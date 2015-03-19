/*
****************************************************************************
* Copyright (C) 2014 Bosch Sensortec GmbH
*
* bme280_support.c
* Date: 2014/12/12
* Revision: 1.0.4 $
*
* Usage: Sensor Driver support file for BME280 sensor
*
****************************************************************************
* License:
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
*   Redistributions of source code must retain the above copyright
*   notice, this list of conditions and the following disclaimer.
*
*   Redistributions in binary form must reproduce the above copyright
*   notice, this list of conditions and the following disclaimer in the
*   documentation and/or other materials provided with the distribution.
*
*   Neither the name of the copyright holder nor the names of the
*   contributors may be used to endorse or promote products derived from
*   this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDER
* OR CONTRIBUTORS BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
* OR CONSEQUENTIAL DAMAGES(INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
* WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE
*
* The information provided is believed to be accurate and reliable.
* The copyright holder assumes no responsibility
* for the consequences of use
* of such information nor for any infringement of patents or
* other rights of third parties which may result from its use.
* No license is granted by implication or otherwise under any patent or
* patent rights of the copyright holder.
**************************************************************************/
/*---------------------------------------------------------------------------*/
/* Includes*/
/*---------------------------------------------------------------------------*/
#include "bme280.h"
#include "bme280_support.h"

#include <linux/i2c.h>
#include <linux/i2c-dev.h>

#include <sys/ioctl.h>

#define BME280_API

static int i2c_xfer(int read, int regaddr, unsigned char* data, int len);

/*----------------------------------------------------------------------------*
*  The following functions are used for reading and writing of
*	sensor data using I2C or SPI communication
*----------------------------------------------------------------------------*/
#ifdef BME280_API
/*	\Brief: The function is used as I2C bus read
 *	\Return : Status of the I2C read
 *	\param dev_addr : The device address of the sensor
 *	\param reg_addr : Address of the first register, will data is going to be read
 *	\param reg_data : This data read from the sensor, which is hold in an array
 *	\param cnt : The no of byte of data to be read
 */
s8 BME280_I2C_bus_read(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt);
 /*	\Brief: The function is used as I2C bus write
 *	\Return : Status of the I2C write
 *	\param dev_addr : The device address of the sensor
 *	\param reg_addr : Address of the first register, will data is going to be written
 *	\param reg_data : It is a value hold in the array,
 *		will be used for write the value into the register
 *	\param cnt : The no of byte of data to be write
 */
s8 BME280_I2C_bus_write(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt);
/*	\Brief: The function is used as SPI bus write
 *	\Return : Status of the SPI write
 *	\param dev_addr : The device address of the sensor
 *	\param reg_addr : Address of the first register, will data is going to be written
 *	\param reg_data : It is a value hold in the array,
 *		will be used for write the value into the register
 *	\param cnt : The no of byte of data to be write
 */
s8 BME280_SPI_bus_write(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt);
/*	\Brief: The function is used as SPI bus read
 *	\Return : Status of the SPI read
 *	\param dev_addr : The device address of the sensor
 *	\param reg_addr : Address of the first register, will data is going to be read
 *	\param reg_data : This data read from the sensor, which is hold in an array
 *	\param cnt : The no of byte of data to be read */
s8 BME280_SPI_bus_read(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt);
/*
 * \Brief: SPI/I2C init routine
*/
s8 I2C_routine(void);
s8 SPI_routine(void);
#endif
/********************End of I2C/SPI function declarations***********************/
/*	Brief : The delay routine
 *	\param : delay in ms
*/
void BME280_delay_msek(u32 msek);
/* This function is an example for reading sensor data
 *	\param: None
 *	\return: communication result
 */
s32 bme280_data_readout_template(void);
/*----------------------------------------------------------------------------*
 *  struct bme280_t parameters can be accessed by using bme280
 *	bme280_t having the following parameters
 *	Bus write function pointer: BME280_WR_FUNC_PTR
 *	Bus read function pointer: BME280_RD_FUNC_PTR
 *	Delay function pointer: delay_msec
 *	I2C address: dev_addr
 *	Chip id of the sensor: chip_id
 *---------------------------------------------------------------------------*/
struct bme280_t bme280;
/* This function is an example for reading sensor data
 *	\param: None
 *	\return: communication result
 */
s32 bme280_data_readout_template(void)
{
	/* The variable used to assign the standby time*/
	u8 v_stand_by_time_u8 = BME280_ZERO_U8X;
	/* The variable used to read uncompensated temperature*/
	s32 v_data_uncomp_tem_s32 = BME280_ZERO_U8X;
	/* The variable used to read uncompensated pressure*/
	s32 v_data_uncomp_pres_s32 = BME280_ZERO_U8X;
	/* The variable used to read uncompensated pressure*/
	s32 v_data_uncomp_hum_s32 = BME280_ZERO_U8X;
	/* The variable used to read real temperature*/
	s32 v_actual_temp_s32 = BME280_ZERO_U8X;
	/* The variable used to read real pressure*/
	u32 v_actual_press_u32 = BME280_ZERO_U8X;
	/* The variable used to read real humidity*/
	u32 v_actual_humity_u32 = BME280_ZERO_U8X;
	/* result of communication results*/
	s32 com_rslt = ERROR;



 /*********************** START INITIALIZATION ************************/
  /*	Based on the user need configure I2C or SPI interface.
  *	It is example code to explain how to use the bme280 API*/
  #ifdef BME280_API
	I2C_routine();
	/*SPI_routine(); */
	#endif
/*--------------------------------------------------------------------------*
 *  This function used to assign the value/reference of
 *	the following parameters
 *	I2C address
 *	Bus Write
 *	Bus read
 *	Chip id
*-------------------------------------------------------------------------*/
	com_rslt = bme280_init(&bme280);

	/*	For initialization it is required to set the mode of
	 *	the sensor as "NORMAL"
	 *	data acquisition/read/write is possible in this mode
	 *	by using the below API able to set the power mode as NORMAL*/
	/* Set the power mode as NORMAL*/
	com_rslt += bme280_set_power_mode(BME280_NORMAL_MODE);
	/*	For reading the pressure, humidity and temperature data it is required to
	 *	set the OSS setting of humidity, pressure and temperature
	 * The "BME280_CTRLHUM_REG_OSRSH" register sets the humidity
	 * data acquisition options of the device.
	 * changes to this registers only become effective after a write operation to
	 * "BME280_CTRLMEAS_REG" register.
	 * In the code automated reading and writing of "BME280_CTRLHUM_REG_OSRSH"
	 * register first set the "BME280_CTRLHUM_REG_OSRSH" and then read and write
	 * the "BME280_CTRLMEAS_REG" register in the function*/
	com_rslt += bme280_set_oversamp_humidity(BME280_OVERSAMP_1X);

	/* set the pressure oversampling*/
	com_rslt += bme280_set_oversamp_pressure(BME280_OVERSAMP_2X);
	/* set the temperature oversampling*/
	com_rslt += bme280_set_oversamp_temperature(BME280_OVERSAMP_4X);
/*--------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*
************************* START GET and SET FUNCTIONS DATA ****************
*---------------------------------------------------------------------------*/
	/* This API used to Write the standby time of the sensor input
	 *	value have to be given
	 *	Normal mode comprises an automated perpetual cycling between an (active)
	 *	Measurement period and an (inactive) standby period.
	 *	The standby time is determined by the contents of the register t_sb.
	 *	Standby time can be set using BME280_STANDBYTIME_125_MS.
	 *	Usage Hint : bme280_set_standbydur(BME280_STANDBYTIME_125_MS)*/

	com_rslt += bme280_set_standby_durn(BME280_STANDBY_TIME_1_MS);

	/* This API used to read back the written value of standby time*/
	com_rslt += bme280_get_standby_durn(&v_stand_by_time_u8);
/*-----------------------------------------------------------------*
************************* END GET and SET FUNCTIONS ****************
*------------------------------------------------------------------*/

/************************* END INITIALIZATION *************************/

/*------------------------------------------------------------------*
************ START READ UNCOMPENSATED PRESSURE, TEMPERATURE
AND HUMIDITY DATA ********
*---------------------------------------------------------------------*/
	/* API is used to read the uncompensated temperature*/
	com_rslt += bme280_read_uncomp_temperature(&v_data_uncomp_tem_s32);

	/* API is used to read the uncompensated pressure*/
	com_rslt += bme280_read_uncomp_pressure(&v_data_uncomp_pres_s32);

	/* API is used to read the uncompensated humidity*/
	com_rslt += bme280_read_uncomp_humidity(&v_data_uncomp_hum_s32);

	/* API is used to read the uncompensated temperature,pressure
	and humidity data */
	com_rslt += bme280_read_uncomp_pressure_temperature_humidity(
	&v_data_uncomp_tem_s32, &v_data_uncomp_pres_s32, &v_data_uncomp_hum_s32);
/*--------------------------------------------------------------------*
************ END READ UNCOMPENSATED PRESSURE AND TEMPERATURE********
*-------------------------------------------------------------------------*/

/*------------------------------------------------------------------*
************ START READ TRUE PRESSURE, TEMPERATURE
AND HUMIDITY DATA ********
*---------------------------------------------------------------------*/
	/* API is used to read the true temperature*/
	/* Input value as uncompensated temperature and output format*/
	com_rslt += bme280_compensate_T_int32(v_data_uncomp_tem_s32);

	/* API is used to read the true pressure*/
	/* Input value as uncompensated pressure */
	com_rslt += bme280_compensate_P_int32(v_data_uncomp_pres_s32);

	/* API is used to read the true humidity*/
	/* Input value as uncompensated humidity and output format*/
	com_rslt += bme280_compensate_H_int32(v_data_uncomp_hum_s32);

	/* API is used to read the true temperature, humidity and pressure*/
	com_rslt += bme280_read_pressure_temperature_humidity(
	&v_actual_press_u32, &v_actual_temp_s32, &v_actual_humity_u32);
/*--------------------------------------------------------------------*
************ END READ TRUE PRESSURE, TEMPERATURE AND HUMIDITY ********
*-------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------*
************************* START DE-INITIALIZATION ***********************
*-------------------------------------------------------------------------*/
	/*	For de-initialization it is required to set the mode of
	 *	the sensor as "SLEEP"
	 *	the device reaches the lowest power consumption only
	 *	In SLEEP mode no measurements are performed
	 *	All registers are accessible
	 *	by using the below API able to set the power mode as SLEEP*/
	 /* Set the power mode as SLEEP*/
	com_rslt += bme280_set_power_mode(BME280_SLEEP_MODE);
/*---------------------------------------------------------------------*
************************* END DE-INITIALIZATION **********************
*---------------------------------------------------------------------*/
return com_rslt;
}

#ifdef BME280_API
#define MASK_DATA1	0xFF
#define MASK_DATA2	0x80
#define MASK_DATA3	0x7F
/*--------------------------------------------------------------------------*
*	The following function is used to map the I2C bus read, write, delay and
*	device address with global structure bme280
*-------------------------------------------------------------------------*/
s8 I2C_routine(void) {
/*--------------------------------------------------------------------------*
 *  By using bme280 the following structure parameter can be accessed
 *	Bus write function pointer: BME280_WR_FUNC_PTR
 *	Bus read function pointer: BME280_RD_FUNC_PTR
 *	Delay function pointer: delay_msec
 *	I2C address: dev_addr
 *--------------------------------------------------------------------------*/
	bme280.bus_write = BME280_I2C_bus_write;
	bme280.bus_read = BME280_I2C_bus_read;
	bme280.dev_addr = BME280_I2C_ADDRESS;
	bme280.delay_msec = BME280_delay_msek;

	return BME280_ZERO_U8X;
}

/*---------------------------------------------------------------------------*
 * The following function is used to map the SPI bus read, write and delay
 * with global structure bme280
 *--------------------------------------------------------------------------*/
s8 SPI_routine(void) {
/*--------------------------------------------------------------------------*
 *  By using bme280 the following structure parameter can be accessed
 *	Bus write function pointer: BME280_WR_FUNC_PTR
 *	Bus read function pointer: BME280_RD_FUNC_PTR
 *	Delay function pointer: delay_msec
 *--------------------------------------------------------------------------*/

	bme280.bus_write = BME280_SPI_bus_write;
	bme280.bus_read = BME280_SPI_bus_read;
	bme280.delay_msec = BME280_delay_msek;

	return BME280_ZERO_U8X;
}

/************** I2C/SPI buffer length ******/
#define	I2C_BUFFER_LEN 256
#define SPI_BUFFER_LEN 5

/*-------------------------------------------------------------------*
*	This is a sample code for read and write the data by using I2C/SPI
*	Use either I2C or SPI based on your need
*	The device address defined in the bme280.h file
*-----------------------------------------------------------------------*/
 /*	\Brief: The function is used as I2C bus write
 *	\Return : Status of the I2C write
 *	\param dev_addr : The device address of the sensor
 *	\param reg_addr : Address of the first register, will data is going to be written
 *	\param reg_data : It is a value hold in the array,
 *		will be used for write the value into the register
 *	\param cnt : The no of byte of data to be write
 */
s8 BME280_I2C_bus_write(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt)
{
	s32 iError = BME280_ZERO_U8X;
	u8 array[I2C_BUFFER_LEN];
	u8 stringpos = BME280_ZERO_U8X;
	array[BME280_ZERO_U8X] = reg_addr;
	for (stringpos = BME280_ZERO_U8X; stringpos < cnt; stringpos++) {
		array[stringpos + BME280_ONE_U8X] = *(reg_data + stringpos);
	}
	/*
	* Please take the below function as your reference for
	* write the data using I2C communication
	* "IERROR = I2C_WRITE_STRING(DEV_ADDR, ARRAY, CNT+1)"
	* add your I2C write function here
	* iError is an return value of I2C read function
	* Please select your valid return value
	* In the driver SUCCESS defined as 0
    * and FAILURE defined as -1
	* Note :
	* This is a full duplex operation,
	* The first read data is discarded, for that extra write operation
	* have to be initiated. For that cnt+1 operation done in the I2C write string function
	* For more information please refer data sheet SPI communication:
	*/
	iError = i2c_xfer(0, reg_addr, array, cnt+1);
	return (s8)iError;
}

 /*	\Brief: The function is used as I2C bus read
 *	\Return : Status of the I2C read
 *	\param dev_addr : The device address of the sensor
 *	\param reg_addr : Address of the first register, will data is going to be read
 *	\param reg_data : This data read from the sensor, which is hold in an array
 *	\param cnt : The no of data byte of to be read
 */
s8 BME280_I2C_bus_read(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt)
{
	s32 iError = BME280_ZERO_U8X;
/*
	u8 array[I2C_BUFFER_LEN] = {BME280_ZERO_U8X};
	u8 stringpos = BME280_ZERO_U8X;
	array[BME280_ZERO_U8X] = reg_addr;
	/* Please take the below function as your reference
	 * for read the data using I2C communication
	 * add your I2C rad function here.
	 * "IERROR = I2C_WRITE_READ_STRING(DEV_ADDR, ARRAY, ARRAY, 1, CNT)"
	 * iError is an return value of SPI write function
	 * Please select your valid return value
     * In the driver SUCCESS defined as 0
     * and FAILURE defined as -1
	for (stringpos = BME280_ZERO_U8X; stringpos < cnt; stringpos++) {
		*(reg_data + stringpos) = array[stringpos];
	}
	 */
	iError = i2c_xfer(1, reg_addr, reg_data, cnt);
	return (s8)iError;
}

/*	\Brief: The function is used as SPI bus read
 *	\Return : Status of the SPI read
 *	\param dev_addr : The device address of the sensor
 *	\param reg_addr : Address of the first register, will data is going to be read
 *	\param reg_data : This data read from the sensor, which is hold in an array
 *	\param cnt : The no of byte of data to be read
 */
s8 BME280_SPI_bus_read(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt)
{
	s32 iError=BME280_ZERO_U8X;
	u8 array[SPI_BUFFER_LEN]={MASK_DATA1};
	u8 stringpos;
	/*	For the SPI mode only 7 bits of register addresses are used.
	The MSB of register address is declared the bit what functionality it is
	read/write (read as 1/write as BME280_ZERO_U8X)*/
	array[BME280_ZERO_U8X] = reg_addr|MASK_DATA2;/*read routine is initiated register address is mask with 0x80*/
	/*
	* Please take the below function as your reference for
	* read the data using SPI communication
	* " IERROR = SPI_READ_WRITE_STRING(ARRAY, ARRAY, CNT+1)"
	* add your SPI read function here
	* iError is an return value of SPI read function
	* Please select your valid return value
	* In the driver SUCCESS defined as 0
    * and FAILURE defined as -1
	* Note :
	* This is a full duplex operation,
	* The first read data is discarded, for that extra write operation
	* have to be initiated. For that cnt+1 operation done in the SPI read
	* and write string function
	* For more information please refer data sheet SPI communication:
	*/
	for (stringpos = BME280_ZERO_U8X; stringpos < cnt; stringpos++) {
		*(reg_data + stringpos) = array[stringpos+BME280_ONE_U8X];
	}
	return (s8)iError;
}

/*	\Brief: The function is used as SPI bus write
 *	\Return : Status of the SPI write
 *	\param dev_addr : The device address of the sensor
 *	\param reg_addr : Address of the first register, will data is going to be written
 *	\param reg_data : It is a value hold in the array,
 *		will be used for write the value into the register
 *	\param cnt : The no of byte of data to be write
 */
s8 BME280_SPI_bus_write(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt)
{
	s32 iError = BME280_ZERO_U8X;
	u8 array[SPI_BUFFER_LEN * BME280_TWO_U8X];
	u8 stringpos = BME280_ZERO_U8X;
	for (stringpos = BME280_ZERO_U8X; stringpos < cnt; stringpos++) {
		/* the operation of (reg_addr++)&0x7F done: because it ensure the
		   BME280_ZERO_U8X and 1 of the given value
		   It is done only for 8bit operation*/
		array[stringpos * BME280_TWO_U8X] = (reg_addr++) & MASK_DATA3;
		array[stringpos * BME280_TWO_U8X + BME280_ONE_U8X] = *(reg_data + stringpos);
	}
	/* Please take the below function as your reference
	 * for write the data using SPI communication
	 * add your SPI write function here.
	 * "IERROR = SPI_WRITE_STRING(ARRAY, CNT*2)"
	 * iError is an return value of SPI write function
	 * Please select your valid return value
	 * In the driver SUCCESS defined as 0
     * and FAILURE defined as -1
	 */
	return (s8)iError;
}

/*	Brief : The delay routine
 *	\param : delay in ms
*/
void BME280_delay_msek(u32 msek)
{
	/*Here you can write your own delay routine*/
	usleep(msek * 1000);
}
#endif

int i2cfd;
static int i2c_xfer(int read, int regaddr, unsigned char* data, int len)
{
	struct i2c_rdwr_ioctl_data iod;
	struct i2c_msg msgs[2];
	int ret;
	if(read) {
		msgs[0].addr = BME280_I2C_ADDRESS;
		msgs[0].flags = 0;
		msgs[0].len = 1;
		msgs[0].buf = (__u8*)&regaddr;
		msgs[1].addr = BME280_I2C_ADDRESS;
		msgs[1].flags = I2C_M_RD;
		msgs[1].len = len;
		msgs[1].buf = data;
	}else {
		msgs[0].addr = BME280_I2C_ADDRESS;
		msgs[0].flags = 0;
		msgs[0].len = len;
		msgs[0].buf = data;
	}
	iod.msgs = msgs;
	iod.nmsgs = read ? 2 : 1;

	ret = ioctl(i2cfd, I2C_RDWR, &iod);
	//printf("I2C %s @%02x len=%d: %02x\n", read ? "RD" : "WR", regaddr, len, read ? data[0] : data[1]);
	if(ret < 0) error(0, errno, "ret = %d", ret);
	return ret < 0 ? -1 : 0;
}

// return 0: ok, <0: error
int i2c_init(void)
{
	i2cfd = open("/dev/i2c-6", O_RDWR);
	if(i2cfd < 0) return -1;
	return 0;
}

// return 0: ok, <0: error
int bme280_appinit(void)
{
	I2C_routine();
	if(bme280_init(&bme280) < 0) return -1;
	return 0;
}

// soft reset
int bme280_reset(void)
{
	return bme280_set_soft_rst();
}

// t in Deg centigrade
// p in Pa
// h in %RH
int bme280_gettph(float* t, float* p, float* h)
{
	int ut, up, uh;
	if(bme280_read_uncomp_pressure_temperature_humidity(&up, &ut, &uh) < 0) return -1;
	*t = bme280_compensate_T_double(ut);
	*p = bme280_compensate_P_double(up);
	*h = bme280_compensate_H_double(uh);
	return 0;
}

// return 0: ok, <0: error
// t in Deg centigrade
int bme280_gett(float* t)
{
	int ut;
	if(bme280_read_uncomp_temperature(&ut) < 0) return -1;
	*t = bme280_compensate_T_double(ut);
	return 0;
}

// return 0: ok, <0: error
// p in Pa
int bme280_getp(float* p)
{
	int up;
	if(bme280_read_uncomp_pressure(&up) < 0) return -1;
	*p = bme280_compensate_P_double(up);
	return 0;
}

// return 0: ok, <0: error
// h in %RH
int bme280_geth(float* h)
{
	int uh;
	if(bme280_read_uncomp_humidity(&uh) < 0) return -1;
	*h = bme280_compensate_H_double(uh);
	return 0;
}

// T/P/H oversampling:
// 	0: off, 1: x1, 2: x2, 3: x4, 4: x8, 5: x16
int bme280_settos(int os)
{
	return bme280_set_oversamp_temperature(os);
}
int bme280_setpos(int os)
{
	return bme280_set_oversamp_pressure(os);
}
int bme280_sethos(int os)
{
	return bme280_set_oversamp_humidity(os);
}

// 0: sleep, 1/2: forced, 3: normal
int bme280_setmode(int mode)
{
	return bme280_set_power_mode(mode);
}

// 0: off, 1: 2x, 2: 4x, 3: 8x, 4: 16x
int bme280_setfilter(int filter)
{
	return bme280_set_filter(filter);
}

// 0: 0.5ms, 1: 62.5ms, ... 7: 20ms
int bme280_settsb(int tsb)
{
	return bme280_set_standby_durn(tsb);
}

// Note I2C bus speed is 100kbps. 400kbps doesn't work.
// co2 in ppm
// resistance in ohm
// tvoc in ppb
int iaq_getall(int* co2, int* resistance, int* tvoc)
{
	struct i2c_rdwr_ioctl_data iod;
	struct i2c_msg msgs[1];
	unsigned char data[9];
	int ret;
	int done = 0;

	while(!done) {
		msgs[0].addr = IAQ_I2C_ADDRESS;
		msgs[0].flags = I2C_M_RD;
		msgs[0].len = sizeof(data);
		msgs[0].buf = data;
		iod.msgs = msgs;
		iod.nmsgs = 1;
	
		ret = ioctl(i2cfd, I2C_RDWR, &iod);
		//printf("I2C %s @%02x len=%d: %02x\n", read ? "RD" : "WR", regaddr, len, read ? data[0] : data[1]);
		if(ret < 0) {
			error(0, errno, "ret = %d", ret);
			return -1;
		}
		if(data[2] == 0x80) {	// ERROR
			fflush(NULL);
			fprintf(stderr, "iAQ returns ERROR(0x80)\n");
			return -1;
		}
		if(data[2] == 0) {	// OK
			done = 1;
			*co2 = ((int)data[0] << 8) + data[1];
			*resistance = ((int)data[4]<<16) + ((int)data[5]<<8) + data[6];
			*tvoc = ((int)data[7] << 8) + data[8];
		}
	}
	
	return 0;
}

