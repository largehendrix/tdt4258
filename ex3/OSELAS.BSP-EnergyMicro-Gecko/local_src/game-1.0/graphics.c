#include "graphics.h"

#define FB_DRAW 0x4680

#define MARGIN 2
#define TEXT_X_ANCHOR 245

int fbfd;
uint16_t* fbp;
int screensize_pixels;
int screensize_bytes;

struct fb_var_screeninfo vinfo;
struct fb_copyarea screen;

int init_framebuffer()
{
    fbfd = open("/dev/fb0", O_RDWR);
    if (fbfd == -1) {
        printf("Error: unable to open framebuffer device.\n");
        return EXIT_FAILURE;
    }

    // Get screen size info
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        printf("Error: unable to get screen info.\n");
        return EXIT_FAILURE;
    }
    printf("Screeninfo: %d x %d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);

    screen.dx = 0;
    screen.dy = 0;
    screen.width = vinfo.xres;
    screen.height = vinfo.yres;

    screensize_pixels = vinfo.xres * vinfo.yres;
    screensize_bytes = screensize_pixels * vinfo.bits_per_pixel / 8;

    fbp = (uint16_t*)mmap(NULL, screensize_bytes, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if ((int)fbp == MAP_FAILED) {
        printf("Error: failed to memorymap framebuffer.\n");
        return EXIT_FAILURE;
    }

    if (init_fonts() == EXIT_FAILURE) {
        printf("Error: failed to initialize fonts.\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < screensize_pixels; i++) {
        fbp[i] = BACKGROUND_COLOR;
    }

    draw_string_at("CURRENT SCORE:", 14, font_small, TEXT_X_ANCHOR, 0);

    return EXIT_SUCCESS;
}

void deinit_framebuffer()
{
    munmap(fbp, screensize_bytes);
    close(fbfd);
}

void refresh_fb()
{
    ioctl(fbfd, FB_DRAW, &screen);
}

void draw_score(int score)
{
    int len = int_len(score);
    char str[len];
    sprintf(str, "%d", score);

    font_t* font = font_medium;
    if (vinfo.xres - TEXT_X_ANCHOR - len*(font->char_w) < 0) {
        font = font_small;
    }

    draw_string_at(str, len, font, TEXT_X_ANCHOR, 10);
}

void clear_score()
{
    for (int y = 10; y < 10 + (font_medium->char_h); y++) {
        for (int x = TEXT_X_ANCHOR; x < vinfo.xres; x++) {
            fbp[y*(vinfo.xres) + x] = BACKGROUND_COLOR;
        }
    }
}

void draw_string_at(char* str, int len, font_t* font, int x_anchor, int y_anchor)
{
    char* glyph = create_glyph(str, len, font);
    int glyph_w = len*(font->char_w);

    for (int y = 0; y < font->char_h; y++) {
        for (int x = 0; x < len*(font->char_w); x++) {
            int glyph_index = y*glyph_w + x;
            int screen_index = (y_anchor + y)*vinfo.xres + (x_anchor + x);

            fbp[screen_index] = glyph[glyph_index] ? Black : BACKGROUND_COLOR;
        }
    }

    free(glyph);
}
