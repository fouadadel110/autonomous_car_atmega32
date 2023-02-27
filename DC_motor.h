
/*
NAME :Fouad Adel Fouad
SWC  :DC_motor
DATE :12/2/2023
*/
#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_


void DC_MOTOR_INIT(u8 Copy_u8PortId, u8 Copy_u8PinId_1,u8 Copy_u8PinId_2,u8 Copy_u8_PWM_PORT,u8 Copy_u8_PWM_PIN,u8 Copy_u8_duty);
void DC_MOTOR_FORWARD(u8 Copy_u8PortId, u8 Copy_u8PinId_1,u8 Copy_u8PinId_2,u8 Copy_u8_duty);
void DC_MOTOR_BACKWARD(u8 Copy_u8PortId, u8 Copy_u8PinId_1,u8 Copy_u8PinId_2,u8 Copy_u8_duty);
void DC_MOTOR_STOP(u8 Copy_u8PortId, u8 Copy_u8PinId_1,u8 Copy_u8PinId_2,u8 Copy_u8_duty);

#endif
