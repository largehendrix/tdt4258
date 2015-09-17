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
	/* pls to help */
	ldr GPIO_LED, =GPIO_PA_BASE
	ldr GPIO_BTN, =GPIO_PC_BASE
	ldr GPIO, =GPIO_BASE

	/* Load CMU base */

	ldr r1, = CMU_BASE

	/* load hfperclken0 */
	ldr r2, [r1, #CMU_HFPERCLKEN0]

	/* set gpio bit */

	mov r3, #1
	lsl r3, r3, #CMU_HFPERCLKEN0_GPIO
	orr r2, r2, r3

	/* store value */
	str r2, [r1, #CMU_HFPERCLKEN0]
	

	/* set low drive strength */
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
    str r1, [GPIO, #GPIO_EXTIFALL]   // We will only be using extifall as we find pushing a button is a more logical choice
    str r1, [GPIO, #GPIO_IEN]

    /* enable interrupt handling */

    ldr r1, =0x802
    ldr r2, =ISER0
    str r1, [r2]




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

	/* Read button */
	ldr r1, [GPIO_BASE, #GPIO_DIN]

	/* Read LED */
	ldr r1, [GPIO_BASE, #GPIO_DOUT]

	/*Shut off lights */
	/*Set lights to  */
	low:
	ldr r1, =0x3
	str r1, [GPIO, #GPIO_CTRL]
	/*Set lights to high */
	high:
	ldr r1, =0x2
	str r1, [GPIO, #GPIO_CTRL]

	      b .  // do nothing
	
	/////////////////////////////////////////////////////////////////////////////
	
        .thumb_func
dummy_handler:  
        b .  // do nothing

