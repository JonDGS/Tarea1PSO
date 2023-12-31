/*
 * "Small Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It requires a STDOUT  device in your system's hardware.
 *
 * The purpose of this example is to demonstrate the smallest possible Hello
 * World application, using the Nios II HAL library.  The memory footprint
 * of this hosted application is ~332 bytes by default using the standard
 * reference design.  For a more fully featured Hello World application
 * example, see the example titled "Hello World".
 *
 * The memory footprint of this example has been reduced by making the
 * following changes to the normal "Hello World" example.
 * Check in the Nios II Software Developers Manual for a more complete
 * description.
 *
 * In the SW Application project (small_hello_world):
 *
 *  - In the C/C++ Build page
 *
 *    - Set the Optimization Level to -Os
 *
 * In System Library project (small_hello_world_syslib):
 *  - In the C/C++ Build page
 *
 *    - Set the Optimization Level to -Os
 *
 *    - Define the preprocessor option ALT_NO_INSTRUCTION_EMULATION
 *      This removes software exception handling, which means that you cannot
 *      run code compiled for Nios II cpu with a hardware multiplier on a core
 *      without a the multiply unit. Check the Nios II Software Developers
 *      Manual for more details.
 *
 *  - In the System Library page:
 *    - Set Periodic system timer and Timestamp timer to none
 *      This prevents the automatic inclusion of the timer driver.
 *
 *    - Set Max file descriptors to 4
 *      This reduces the size of the file handle pool.
 *
 *    - Check Main function does not exit
 *    - Uncheck Clean exit (flush buffers)
 *      This removes the unneeded call to exit when main returns, since it
 *      won't.
 *
 *    - Check Don't use C++
 *      This builds without the C++ support code.
 *
 *    - Check Small C library
 *      This uses a reduced functionality C library, which lacks
 *      support for buffering, file IO, floating point and getch(), etc.
 *      Check the Nios II Software Developers Manual for a complete list.
 *
 *    - Check Reduced device drivers
 *      This uses reduced functionality drivers if they're available. For the
 *      standard design this means you get polled UART and JTAG UART drivers,
 *      no support for the LCD driver and you lose the ability to program
 *      CFI compliant flash devices.
 *
 *    - Check Access device drivers directly
 *      This bypasses the device file system to access device drivers directly.
 *      This eliminates the space required for the device file system services.
 *      It also provides a HAL version of libc services that access the drivers
 *      directly, further reducing space. Only a limited number of libc
 *      functions are available in this configuration.
 *
 *    - Use ALT versions of stdio routines:
 *
 *           Function                  Description
 *        ===============  =====================================
 *        alt_printf       Only supports %s, %x, and %c ( < 1 Kbyte)
 *        alt_putstr       Smaller overhead than puts with direct drivers
 *                         Note this function doesn't add a newline.
 *        alt_putchar      Smaller overhead than putchar with direct drivers
 *        alt_getchar      Smaller overhead than getchar with direct drivers
 *
 */
#include "sys/alt_irq.h"
#include "sys/alt_stdio.h"
#include "altera_avalon_pio_regs.h"
#include "altera_avalon_timer_regs.h"

#include "system.h"

#include "alt_types.h"


int seconds=0;
int miliseconds=0;
int minutes=0;
int mode=0;
int stop=0;
int start=0;

typedef int digits_t[6];

/** @brief Divides the digits of number into an array
*		   numberDigits
*	@param number: number being divide on the array
*	@param numberDigits: array storing the digits
*	@return void
**/
void divideDigits(int number, digits_t numberDigits){
	int i;
	int currentDigit;

	for(i=0;i<6;i++){
		currentDigit=number%10;
		number=number/10;
		numberDigits[i]=currentDigit;

	}

}

/** @brief Return the corresponding display code for a
*		   digit going to the display
*	@param digit: Number being converted
*	@return int numbers' display code
**/
int getDigitDisplay(int digit){

	int digits[10]={64,121,36,48,25,18,2,120,0,16};
	return digits[digit];
}

/** @brief Adds the converted digit back to digits array
*	@param digits: Array of digits being displayed
*	@return void
**/
void numberDisplayDigits(digits_t digits){

	int i;
	for(i=0;i<6;i++){
		digits[i]=getDigitDisplay(digits[i]);
	}


}

/** @brief Writes the digits to the 7 segments on the FPGA
*	@param digits: Array of digits being displayed
*	@return void
**/
void writeDisplays(digits_t digits){
	numberDisplayDigits(digits);
	IOWR_ALTERA_AVALON_PIO_DATA(PIO_DISPLAY_0_BASE, digits[0]);
	IOWR_ALTERA_AVALON_PIO_DATA(PIO_DISPLAY_1_BASE, digits[1]);
	IOWR_ALTERA_AVALON_PIO_DATA(PIO_DISPLAY_2_BASE, digits[2]);
	IOWR_ALTERA_AVALON_PIO_DATA(PIO_DISPLAY_3_BASE, digits[3]);
	IOWR_ALTERA_AVALON_PIO_DATA(PIO_DISPLAY_4_BASE, digits[4]);
	IOWR_ALTERA_AVALON_PIO_DATA(PIO_DISPLAY_5_BASE, digits[5]);

}

/** @brief Runs a cycle of the miliseconds mode
*	@return void
**/
static void timer_miliseconds(){
	miliseconds++;
	digits_t digits={0,0,0,0,0,0};
	divideDigits(miliseconds,digits);
	writeDisplays(digits);
}

/** @brief Runs a cycle of the seconds mode
*	@return void
**/
static void timer_seconds(){
	miliseconds++;
	seconds+= (miliseconds/1000);
	miliseconds=miliseconds%1000;
	digits_t digits={0,0,0,0,0,0};
	divideDigits(seconds,digits);
	writeDisplays(digits);
}

/** @brief Runs a cycle of the minutes, seconds
*		   and miliseconds mode
*	@return void
**/
static void timer_full(){
	miliseconds++;
	seconds+=miliseconds/1000;
	miliseconds=miliseconds%1000;
	minutes+=seconds/60;
	seconds=seconds%60;
	digits_t digits={0,0,0,0,0,0};


	int minutesArray[2];
	int secondsArray[2];
	int milisecondsArray[2];

	divideDigits(miliseconds,digits);
	milisecondsArray[0]=digits[1];
	milisecondsArray[1]=digits[2];

	divideDigits(seconds,digits);
	secondsArray[0]=digits[0];
	secondsArray[1]=digits[1];


	divideDigits(minutes,digits);
	minutesArray[0]=digits[0];
	minutesArray[1]=digits[1];


	digits[0]=milisecondsArray[0];
	digits[1]=milisecondsArray[1];
	digits[2]=secondsArray[0];
	digits[3]=secondsArray[1];
	digits[4]=minutesArray[0];
	digits[5]=minutesArray[1];



	writeDisplays(digits);
}

/** @brief Runs the interrupt for timer
*	@return void
**/
static void timer_isr(void *context)
{
	(void) context;

	if(stop==0 && start==1){
		if(mode==0)timer_miliseconds();
		else if(mode==1)timer_seconds();
		else timer_full();
	}
	IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_0_BASE, 0);

}


/** @brief Runs the interrupt for stopping
*	@return void
**/
static void stop_isr(void *context)
{
	stop=1;

}

/** @brief Runs the interrupt for starting
*	@return void
**/
static void start_isr(void *context)
{
	if(start==0){
		mode=IORD_ALTERA_AVALON_PIO_DATA(PIO_SW_SELECTOR_BASE);
		digits_t digits={0,0,0,0,0,0};
		writeDisplays(digits);
	}
	start=1;

}




int main()
{

  alt_ic_isr_register(
		  TIMER_0_IRQ_INTERRUPT_CONTROLLER_ID,
		  TIMER_0_IRQ,
		  timer_isr,
		  NULL ,
		  NULL);

  IOWR_ALTERA_AVALON_TIMER_CONTROL(
		  TIMER_0_BASE,
				  ALTERA_AVALON_TIMER_CONTROL_ITO_MSK
				  | ALTERA_AVALON_TIMER_CONTROL_CONT_MSK);


  alt_ic_isr_register(
		  PIO_BUTTON_STOP_IRQ_INTERRUPT_CONTROLLER_ID,
		  PIO_BUTTON_STOP_IRQ,
  		  stop_isr,
  		  NULL ,
  		  NULL);
  IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIO_BUTTON_STOP_BASE, 0x1);


  alt_ic_isr_register(
		  PIO_SW_INIT_IRQ_INTERRUPT_CONTROLLER_ID,
		  PIO_SW_INIT_IRQ,
    		  start_isr,
    		  NULL ,
    		  NULL);
  IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIO_SW_INIT_BASE, 0x1);

  while (1);

}
