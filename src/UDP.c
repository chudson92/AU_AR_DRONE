#include "UDP.h"

 void takeoff(){
	char buff[100];
	sprintf(buff, "AT*REF=%d,290718208\r", seq++);
	int buff_len = strlen( buff );
	navdata_write ((int8_t*)buff);

}
 void forward(){
	char buff[100];
	sprintf(buff, "AT*PCMD=%d,1,0,%d,0,0\r", seq++, *(int*)&forwardPower);
	int buff_len = strlen( buff );
	navdata_write ((int8_t*)buff);

}
 void left(){
	char buff[100];
	sprintf(buff, "AT*PCMD=%d,1,%d,0,0,0\r", seq++, *(int*)&tilt_left);
	int buff_len = strlen( buff );
	navdata_write ((int8_t*)buff);

}
 void right(){
	char buff[100];
	sprintf(buff, "AT*PCMD=%d,1,%d,0,0,0\r", seq++, *(int*)&tilt_right);
	int buff_len = strlen( buff );
	navdata_write ((int8_t*)buff);

}
 void rotate(){
	char buff[100];
	sprintf(buff, "AT*PCMD=%d,1,0,0,0,%d\r", seq++, *(int*)&rotPower);
	navdata_write ((int8_t*)buff);

}
 void hover(){
	char buff[100];
	sprintf(buff, "AT*PCMD=%d,0,0,0,0,0\r", seq++);
	int buff_len = strlen( buff );
	navdata_write ((int8_t*)buff);

}
 void land(){
	char buff[100];
	sprintf(buff, "AT*REF=%d,290717696\r\0", seq++);
	int buff_len = strlen( buff );
	navdata_write ((int8_t*)buff);

}
 void watchDog(){
	char buff[100];
	sprintf(buff, "AT*COMWDG=%d\r", seq++);
	int buff_len = strlen( buff );
	navdata_write ((int8_t*)buff);
}

 void calib_magneto() {
 	char buff[100];
 	sprintf(buff, "AT*CALIB=%d,1,\r", seq++);
 	navdata_write ((int8_t*)buff);
 }

 void setup(void) {
 	int32_t one = 1,zero=0;
 	if((at_socket = socket (AF_INET, SOCK_DGRAM, 0)) < 0){
         	printf ("at_socket error: %s\n", strerror(errno));
         	return;
     	}

 	if((navdata_socket = socket (AF_INET, SOCK_DGRAM, 0)) < 0){
         	printf ("navdata_socket: %s\n", strerror(errno));
         	return;
     	}

 	//for recvfrom
 	pc_addr.sin_family = AF_INET;
 	pc_addr.sin_addr.s_addr = htonl(INADDR_ANY);
 	pc_addr.sin_port = htons(NAVDATA_PORT);

     	//for sendto AT
     	drone_at.sin_family = AF_INET;
     	drone_at.sin_addr.s_addr = inet_addr(WIFI_MYKONOS_IP);
     	drone_at.sin_port = htons(AT_PORT);

     	//for sendto navadata init
     	drone_nav.sin_family = AF_INET;
     	drone_nav.sin_addr.s_addr = inet_addr(WIFI_MYKONOS_IP);
     	drone_nav.sin_port = htons(NAVDATA_PORT);

 	if(bind( navdata_socket, (struct sockaddr *)&pc_addr, sizeof(pc_addr)) < 0){
         	printf ("bind: %s\n", strerror(errno));
         	return;
    	 }

     	//set unicast mode on
    	 sendto(navdata_socket, &one, 4, 0, (struct sockaddr *)&drone_nav, sizeof(drone_nav));
 }

 void navdata_write(char *command) {
 	sendto(at_socket, command, strlen(command), 0, (struct sockaddr*)&drone_at, sizeof(drone_at) );
 }

 void navdata_read(void) {
	//printf("read navdata\n");
 	int size, l;
 	size = 0;
 	size = recvfrom ( navdata_socket, &navdata_message[0], NAVDATA_BUFFER_SIZE, 0x0, (struct sockaddr *)&from, (socklen_t *)&l);
 	int i;
 	//for (i = 16; i < size; i++) printf("%x ", navdata_message[i]);
	//printf("out of read\n");
 }

 void get_Navdata_demo(void) {
 	char command[100];
 	sprintf(command,"AT*CONFIG=%d,\"general:navdata_demo\",\"TRUE\"\r",seq);
 	navdata_write(command);
 	seq++;
 }

 void parse_navdata() {
	//printf("parse navdata\n");
 	//uint8_t navdata_message[index] = navdata_message;
	int index = 0;
 	int32_t header;
 	header = navdata_message[index];
 	index += 1;
 	header |= (navdata_message[index] << 8);
 	index += 1;
 	header |= (navdata_message[index] << 16);
 	index += 1;
 	header |= (navdata_message[index] << 24);
 	index += 1;
 	if (header != 0x55667788) {
 		return;
 	}
 	drone_state = navdata_message[index];
 	index += 1;
 	drone_state |= (navdata_message[index] << 8);
 	index += 1;
 	drone_state |= (navdata_message[index] << 16);
 	index += 1;
 	drone_state |= (navdata_message[index] << 24);
 	index += 1;
 	//printf("drone_state: %x\n", drone_state);

 	sequenceNumber = navdata_message[index];
 	index += 1;
 	sequenceNumber |= (navdata_message[index] << 8);
 	index += 1;
 	sequenceNumber |= (navdata_message[index] << 16);
 	index += 1;
 	sequenceNumber |= (navdata_message[index] << 24);
 	index += 1;
 	//printf("seq_num: %x\n", sequenceNumber);

 	visionFlag = navdata_message[index];
 	index += 1;
 	visionFlag |= (navdata_message[index] << 8);
 	index += 1;
 	visionFlag |= (navdata_message[index] << 16);
 	index += 1;
 	visionFlag |= (navdata_message[index] << 24);
 	index += 1;
 	//printf("Vision Flag: %x\n", visionFlag);

 	while (index != -1) {
 		getNextOption(&index);
 	}

 }

void getNextOption(int *index) {
 	int16_t id;
 	int16_t option_size = 0;
 	id = (uint8_t)navdata_message[*index];
 	*index += 1;
 	id |= ((uint8_t)navdata_message[*index] << 8);
 	*index += 1;
 	//printf("id: %x\n");
 	option_size = (uint8_t)navdata_message[*index];
 	*index += 1;
 	option_size |= ((uint8_t)navdata_message[*index] << 8);
 	*index += 1;
 	//printf("size: %x\n", option_size);
 	//int i;
 	//for(i = *index + option_size - 4; i < 500; i++) printf("%x ", navdata_message[i]);
 	//printf("\n");
 	//sleep(1);
 	switch (id) {
 		case 0: //navdata_demo
 			//printf("\nDEMO\n");
 			parse_navdemo(index);
 			break;
 		case -1: //checksum
 			//printf("\nCHECK\n");
 			parse_checksum(index);
 			break;
 		default:
 			//printf("\nDEFAULT\n");
 			*index += option_size -4;
 			 break;
 	}
 }
 void parse_navdemo(int *index) {
 	int32_t temp;
 	navdemoData.ctrl_state = navdata_message[*index];
 	*index += 1;
 	navdemoData.ctrl_state |= (navdata_message[*index] << 8);
 	*index += 1 ;
 	navdemoData.ctrl_state |= (navdata_message[*index] << 16);
 	*index += 1 ;
 	navdemoData.ctrl_state |= (navdata_message[*index] << 24);
 	*index += 1 ;

 	navdemoData.vbat_flying_percentage = navdata_message[*index];
 	*index += 1 ;
 	navdemoData.vbat_flying_percentage |= (navdata_message[*index] << 8);
 	*index += 1 ;
 	navdemoData.vbat_flying_percentage |= (navdata_message[*index] << 16);
 	*index += 1 ;
 	navdemoData.vbat_flying_percentage |= (navdata_message[*index] << 24);
 	*index += 1 ;
 	//printf("vbat_: %d%%\n", navdemoData.vbat_flying_percentage);

 	temp = navdata_message[*index];
 	*index += 1 ;
 	temp |= (navdata_message[*index] << 8);
 	*index += 1 ;
 	temp |= (navdata_message[*index] << 16);
 	*index += 1 ;
 	temp |= (navdata_message[*index] << 24);
 	*index += 1 ;
 	navdemoData.theta = *(float *)&temp;
 	navdemoData.theta /= 1000;

 	temp = navdata_message[*index];
 	*index += 1 ;
 	temp |= (navdata_message[*index] << 8);
 	*index += 1 ;
 	temp |= (navdata_message[*index] << 16);
 	*index += 1 ;
 	temp |= (navdata_message[*index] << 24);
 	*index += 1 ;
 	navdemoData.phi = *(float *)&temp;
 	navdemoData.phi /= 1000;

 	temp = navdata_message[*index];
 	*index += 1 ;
 	temp |= (navdata_message[*index] << 8);
 	*index += 1 ;
 	temp |= (navdata_message[*index] << 16);
 	*index += 1 ;
 	temp |= (navdata_message[*index] << 24);
 	*index += 1 ;
 	navdemoData.psi = *(float *)&temp;
 	navdemoData.psi /= 1000;
 	//printf("YAW: %f \n", navdemoData.psi);

 	navdemoData.altitude = navdata_message[*index];
 	*index += 1 ;
 	navdemoData.altitude |= (navdata_message[*index] << 8);
 	*index += 1 ;
 	navdemoData.altitude |= (navdata_message[*index] << 16);
 	*index += 1 ;
 	navdemoData.altitude |= (navdata_message[*index] << 24);
 	*index += 1 ;
 	//printf("alt: %f in\n", navdemoData.altitude);

 	temp = navdata_message[*index];
 	*index += 1 ;
 	temp |= (navdata_message[*index] << 8);
 	*index += 1 ;
 	temp |= (navdata_message[*index] << 16);
 	*index += 1 ;
 	temp |= (navdata_message[*index] << 24);
 	*index += 1 ;
 	navdemoData.vx = *(float *)&temp;
 	//printf("vx: %f\n", navdemoData.vx);

 	temp = navdata_message[*index];
 	*index += 1 ;
 	temp |= (navdata_message[*index] << 8);
 	*index += 1 ;
 	temp |= (navdata_message[*index] << 16);
 	*index += 1 ;
 	temp |= (navdata_message[*index] << 24);
 	*index += 1 ;
 	navdemoData.vy = *(float *)&temp;
 	//printf("vy: %f\n", navdemoData.vy);

 	temp = navdata_message[*index];
 	*index += 1 ;
 	temp |= (navdata_message[*index] << 8);
 	*index += 1 ;
 	temp |= (navdata_message[*index] << 16);
 	*index += 1 ;
 	temp |= (navdata_message[*index] << 24);
 	*index += 1 ;
 	navdemoData.vz = *(float *)&temp;
 	//printf("vz: %f\n", navdemoData.vz);

 	navdemoData.num_frames = navdata_message[*index];
 	*index += 1 ;
 	navdemoData.num_frames |= (navdata_message[*index] << 8);
 	*index += 1 ;
 	navdemoData.num_frames |= (navdata_message[*index] << 16);
 	*index += 1 ;
 	navdemoData.num_frames |= (navdata_message[*index] << 24);
 	*index += 1 ;

 	//skip over all the other junk for right now
 	*index += 104;
 }

 void parse_checksum(int *index) {
	/*printf("before null %x\n", ptr);*/
 	*index = -1;
 	/*printf("after null %x\n", ptr);*/
 }

 float getVx() {
	return navdemoData.vx;
 }

 float getVy() {
	 return navdemoData.vy;
 }

