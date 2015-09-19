        .syntax unified
	
	      .include "efm32gg.s"

	/////////////////////////////////////////////////////////////////////////////
	//
  // Exception vector table
  // This table contains addresses for all exception handlers
	//
	/////////////////////////////////////////////////////////////////////////////
	
        .section .vectors
	
	      .long   stack_top               /* Top of Stack                 */
	      .long   _reset                  /* Reset Handler                */
	      .long   dummy_handler           /* NMI Handler                  */
	      .long   dummy_handler           /* Hard Fault Handler           */
	      .long   dummy_handler           /* MPU Fault Handler            */
	      .long   dummy_handler           /* Bus Fault Handler            */
	      .long   dummy_handler           /* Usage Fault Handler          */
	      .long   dummy_handler           /* Reserved                     */
	      .long   dummy_handler           /* Reserved                     */
	      .long   dummy_handler           /* Reserved                     */
	      .long   dummy_handler           /* Reserved                     */
	      .long   dummy_handler           /* SVCall Handler               */
	      .long   dummy_handler           /* Debug Monitor Handler        */
	      .long   dummy_handler           /* Reserved                     */
	      .long   dummy_handler           /* PendSV Handler               */
	      .long   dummy_handler           /* SysTick Handler              */

	      /* External Interrupts */
	      .long   dummy_handler
	      .long   gpio_handler            /* GPIO even handler */
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   gpio_handler            /* GPIO odd handler */
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler

	      .section .text

	/////////////////////////////////////////////////////////////////////////////
	//
	// Reset handler
  // The CPU will start executing here after a reset
	//
	/////////////////////////////////////////////////////////////////////////////
	 
	      .globl  _reset
	      .type   _reset, %function
        .thumb_func
_reset: 
    //aliases
    GPIO_LED .req r5
    GPIO_BTN .req r6
    GPIO .req r10
    CMU .req r7


	/* Load bases */
	ldr GPIO_LED, =GPIO_PA_BASE
	ldr GPIO_BTN, =GPIO_PC_BASE
	ldr GPIO, =GPIO_BASE
	ldr CMU, = CMU_BASE

	/* load hfperclken0 */
	ldr r2, [CMU, #CMU_HFPERCLKEN0]

	/* set gpio bit for clock */

	mov r3, #1
	lsl r3, r3, #CMU_HFPERCLKEN0_GPIO
	orr r2, r2, r3

	/* store value */
	str r2, [CMU, #CMU_HFPERCLKEN0]
	

	/* set high drive strength */
	ldr r2, = 0x2
	mov r3, #GPIO_CTRL


	/* set pins 8-15 to output */
	ldr r2, = 0x55555555
	mov r3, #GPIO_MODEH
    add r3, r3, GPIO_LED
    str r2, [r3]

	/* set pins 0-7 to input */
	ldr r2, = 0x33333333
	mov r3, #GPIO_MODEL
    add r3, r3, GPIO_BTN
    str r2, [r3]

    /* internal pull-up */
    ldr r2, = 0xff
    str r2, =[GPIO_BTN, #GPIO_DOUT]

    /* enable gpio interrupt */
    ldr r1, = 0x22222222
    str r1, [GPIO, #GPIO_EXTIPSELL]

    /* enable interrupt on button push*/
    ldr r1, =0xff
    str r1, [GPIO, #GPIO_EXTIFALL]   // Enable interrupt on button push
    // str r1, [GPIO, #GPIO_EXTIRISE] // When enabled will enable interrupt on button release
    str r1, [GPIO, #GPIO_IEN]



    /* enable interrupt handling */

    ldr r1, =0x802
    ldr r2, =ISER0
    str r1, [r2]


sleep:
	/* enable sleep */
	ldr r1, =SCR
	mov r2, #6
	str r2,[r1]
	wfi




	/////////////////////////////////////////////////////////////////////////////
	//
  // GPIO handler
  // The CPU will jump here when there is a GPIO interrupt
	//
	/////////////////////////////////////////////////////////////////////////////
	
        .thumb_func
gpio_handler:  


	/* Clear interrupt */
	ldr r1, [GPIO, #GPIO_IF]
	str r1, [GPIO, #GPIO_IFC]


	r2, =GPIO_BTN
	lsl r2, r2, #8
	str GPIO_LED[r2]
	
	/////////////////////////////////////////////////////////////////////////////
	
        .thumb_func
dummy_handler:  
        b .  // do nothing

