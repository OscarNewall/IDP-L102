#include <Adafruit_LSM6DS3.h>
#include <Ticker.h>

#define measurement 1 // 1 for acceleration, 2 for gyro
#define data_points 512 // how many datapoints to record in each array
//#define repeats 20 // how many arrays to send
#define interval 150 // ticker interval in microseconds

#define LSM_CS 30
#define LSM_SCK 34
#define LSM_MISO 33
#define LSM_MOSI 32
#define LSM_INT 31

void callback_save_measurement();

Adafruit_LSM6DS3 imu;
Ticker timer(callback_save_measurement, interval, 0, MICROS_MICROS);
float data[data_points];
int index_datapoint = 0;
int index_array = 0;

void setup() {
    Serial.begin(9600);
    if(!imu.begin_SPI(LSM_CS, LSM_SCK, LSM_MISO, LSM_MOSI)) {
        Serial.println("Failed to find IMU");
    }
    /**
    LSM6DS_RATE_12_5_HZ,
    LSM6DS_RATE_26_HZ,
    LSM6DS_RATE_52_HZ,
    LSM6DS_RATE_104_HZ,
    LSM6DS_RATE_208_HZ,
    LSM6DS_RATE_416_HZ,
    LSM6DS_RATE_833_HZ,
    LSM6DS_RATE_1_66K_HZ,
    LSM6DS_RATE_3_33K_HZ,
    LSM6DS_RATE_6_66K_HZ,
    */
    imu.setAccelDataRate(LSM6DS_RATE_6_66K_HZ);
    imu.setGyroDataRate(LSM6DS_RATE_12_5_HZ);
    /**
    LSM6DS_ACCEL_RANGE_2_G,
    LSM6DS_ACCEL_RANGE_16_G,
    LSM6DS_ACCEL_RANGE_4_G,
    LSM6DS_ACCEL_RANGE_8_G
    */
    imu.setAccelRange(LSM6DS_ACCEL_RANGE_2_G);
    /**
    LSM6DS_GYRO_RANGE_125_DPS = 0b0010,
    LSM6DS_GYRO_RANGE_250_DPS = 0b0000,
    LSM6DS_GYRO_RANGE_500_DPS = 0b0100,
    LSM6DS_GYRO_RANGE_1000_DPS = 0b1000,
    LSM6DS_GYRO_RANGE_2000_DPS = 0b1100,
    */
    imu.setGyroRange(LSM6DS_GYRO_RANGE_125_DPS);
}

void loop() {
    // put your main code here, to run repeatedly:
    timer.update();
    if(index_datapoint = data_points) {
        Serial.write((byte*)data, data_points * sizeof(data[0]));
        Serial.println();
        index_datapoint = 0;
        index_array++;
    }
}

void callback_save_measurement() {
    sensors_event_t accel;
    sensors_event_t gyro;
    sensors_event_t temp;
    imu.getEvent(&accel, &gyro, &temp);
    int sensor = measurement;
    if(sensor == 1) {
        data[index_datapoint] = accel.acceleration.x;
    }
    else if (sensor ==2) {
        data[index_datapoint] = gyro.gyro.z;
    }
    index_datapoint++;
}