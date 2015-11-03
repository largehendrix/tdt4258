/*
 * This is a demo Linux kernel module.
 */
 /* Imports and libs */
 #include <linux/kernel.h>
 #include <linux/module.h>
 #include <linux/init.h>
 #include <linux/fs.h>
 #include <linux/cdev.h>
 #include <linux/device.h>
 #include <linux/ioport.h>
 #include <asm/io.h>
 #include <linux/uaccess.h>
 #include <linux/interrupt.h>
 #include <asm/signal.h>
 #include <linux/poll.h>
 #include <asm/siginfo.h>
 #include <linux/signal.h>
 #include <linux/moduleparam.h>
 #include <linux/kdev_t.h>

 #include "efm32gg.h"

 /* Definations */
 #define DRIVER "gamepad"
 #define GPIO_EVEN_IRC_NUM 17
 #define GPIO_ODD_IRC_NUM 18

 /* Module variables */
 module_init(init_driver);
 module_exit(cleanup_driver);
 MODULE_DESCRIPTION("TDT4258 exercise gamepad driver");
 MODULE_LICENSE("GPL");

 /* Static vars */
 struct cdev driver_cdev;
 struct class *cl;
 dev_t devno;
 struct resource *resource;
 struct fasync_struct *async_queue;

 /*Prototypes*/
 static int __init init_driver();
 static void __exit cleanup_driver();
 static int open_gamepad(struct inode *node, struct file *filp);
 static int release_gamepad(struct inode *inode, struct file *filp);
 static ssize_t read_gamepad(struct file *filp, char __user *buff, size_t count, loff_t *offp);
 static ssize_t write_gamepad(struct file *filp, const char __user *buf, size_t count, loff_t *offp);
 irqreturn_t GPIO_interrupt_handler(int irq, void *dev_id, struct pt_regs *regs);
 static int driver_fasync(int fd, struct file *filp, int mode);

 /* File Operations defined by driver */
 static struct file_operations fops = {
	.owner = THIS_MODULE,
	.read = read_gamepad,
	.write = write_gamepad,
	.open = open_gamepad,
	.release = release_gamepad,
        .fasync = gamepad_fasync,

};

static int gamepad_fasync(int fd, struct file *filp, int mode){
	return fasync_helper(fd, filp, mode, &async_queue);
}

irqreturn_t GPIO_interrupt_handler(int irq, void *dev_id, struct pt_regs *regs){

	printk(KERN_ALERT "Handling GPIO interrupt\n");
	iowrite32(0xFF, GPIO_IFC);
	if(async_queue){
		kill_fasync(&async_queue, SIGIO, POLL_IN);
	}
	return IRQ_HANDLED;
}

/*
 * Function to insert this module into kernel space
 * Returns 0 if successfull, otherwise -1
 */

static int __init init_driver(void)
{

	/* Get a major number for the device, minor default 0 */
	int err = alloc_chrdev_region(&devno, 0, 1, DRIVER);

	/* Initialize the char device structure */
	cdev_init(&driver_cdev, &fops);  	    //Init the cdev
	driver_cdev.owner = THIS_MODULE;


	/* Register char device structure to the kernel*/
	err = cdev_add(&driver_cdev, devno, 1);


	/* Error check */
	if(err < 0){
		printk("Error %d", err);
		return -1;
	}else {
		printk("Device added to the kernel sucessfully\n");
	}

	/*Make device visible in user space */
	cl = class_create(THIS_MODULE, DRIVER);
	device_create(cl, NULL, devno, NULL, DRIVER);

	/* Request memory region of the GPIO registers */
	resource = request_mem_region(GPIO_PC_BASE,GPIO_IFC - GPIO_PA_BASE, DRIVER);

	if(resource != NULL){
		printk("Got requested memory region\n");
	}


	/*Configure buttons for output*/
	iowrite32(0x33333333, GPIO_PC_MODEL);
	iowrite32(0xff, GPIO_PC_DOUT);

	/* Register interrupt handler */
	request_irq(GPIO_EVEN_IRC_NUM,(irq_handler_t)GPIO_interrupt_handler, 0, DRIVER, &driver_cdev);
	request_irq(GPIO_ODD_IRC_NUM, (irq_handler_t)GPIO_interrupt_handler, 0, DRIVER, &driver_cdev);

	/* Configure hardware interrupt */
	iowrite32(0x22222222, GPIO_EXTIPSELL);
	iowrite32(0xff, GPIO_EXTIFALL);
	iowrite32(0xff, GPIO_IEN);


	return 0;
}

/* Cleans module from kernel space */
static void __exit cleanup_driver(void)
{
		/* Remove the cdev structure from the system */
	cdev_del(&driver_cdev);

	/* Free the requested memory region */
	release_mem_region(GPIO_PC_BASE, GPIO_IFC - GPIO_PA_BASE);

	/*Unregister the interrupt handler and disable the interrupt line*/
	free_irq(GPIO_EVEN_IRQ_NUM, &driver_cdev);
	free_irq(GPIO_ODD_IRQ_NUM, &driver_cdev);

	printk("Finished with cleanup\n");
}


/*Enables program to open driver */
static int open_gamepad(struct inode *node, struct file *filp){
	printk("The gamepad is ready to go\n");

	return 0;
}

/*Enables program to release driver */
static int release_gamepad(struct inode *inode, struct file *filp){
	printk("Finished with the driver\n");
	return 0;
}


/*Enables program to read from driver */
static ssize_t read_gamepad(struct file *filp, char __user *buff, size_t count, loff_t *offp){

	uint32_t data = ioread32(GPIO_PC_DIN);
	copy_to_user(buff, &data, 1);

	return 1;

}


static ssize_t write_gamepad(struct file *filp, const char __user *buf, size_t count, loff_t *offp){
		printk(KERN_INFO "Nothing to write to");
    return 1;
}
