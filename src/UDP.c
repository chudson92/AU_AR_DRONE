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
 	int size, l;
 	size = 0;
 	size = recvfrom ( navdata_socket, &navdata_message[0], NAVDATA_BUFFER_SIZE, 0x0, (struct sockaddr *)&from, (socklen_t *)&l);
 	printf("%x\n", navdata_message[0]);
 	printf("flying percentage : %d\n", navdemoData.vbat_flying_percentage);
 	//printf("psi : %f", navdemoData.psi);
 }

 void get_Navdata_demo(void) {
 	char command[100];
 	sprintf(command,"AT*COMWDG=%d\r",seq);
 	navdata_write(command);
 	printf("seq : %d \n", seq);
 	seq++;
 }

 int parse_navdata() {
 	uint8_t *ptr = navdata_message;
 	int32_t header;
 	header = *ptr;
 	ptr++;
 	header |= (*ptr << 8);
 	ptr++;
 	header |= (*ptr << 16);
 	ptr++;
 	header |= (*ptr << 24);
 	ptr++;
 	if (header != 0x55667788) {
 		return 0;
 	}
 	drone_state = *ptr;
 	ptr++;
 	drone_state |= (*ptr << 8);
 	ptr++;
 	drone_state |= (*ptr << 16);
 	ptr++;
 	drone_state |= (*ptr << 24);
 	ptr++;

 	sequenceNumber = *ptr;
 	ptr++;
 	sequenceNumber |= (*ptr << 8);
 	ptr++;
 	sequenceNumber |= (*ptr << 16);
 	ptr++;
 	sequenceNumber |= (*ptr << 24);
 	ptr++;

 	visionFlag = *ptr;
 	ptr++;
 	visionFlag |= (*ptr << 8);
 	ptr++;
 	visionFlag |= (*ptr << 16);
 	ptr++;
 	visionFlag |= (*ptr << 24);
 	ptr++;

 	while (ptr != NULL) {
 		getNextOption(ptr);
 	}
 }

void getNextOption(uint8_t *ptr) {
 	int16_t id;
 	id = *ptr;
 	ptr++;
 	id |= (*ptr << 8);

 	switch (id) {
 		case 0: //navdata_demo
 			parse_navdemo(ptr);
 			break;
 		case 10: //altitude
 			break;
 		case -1: //checksum
 			parse_checksum(ptr);
 			break;
 		default:
 			 break;
 	}
 }
 void parse_navdemo(uint8_t *ptr) {
 	int32_t temp;
 	ptr += 2; //skip over size
 	navdemoData.ctrl_state = *ptr;
 	ptr++;
 	navdemoData.ctrl_state |= (*ptr << 8);
 	ptr++;
 	navdemoData.ctrl_state |= (*ptr << 16);
 	ptr++;
 	navdemoData.ctrl_state |= (*ptr << 24);
 	ptr++;

 	navdemoData.vbat_flying_percentage = &*ptr;
 	ptr++;
 	navdemoData.vbat_flying_percentage |= (*ptr << 8);
 	ptr++;
 	navdemoData.vbat_flying_percentage |= (*ptr << 16);
 	ptr++;
 	navdemoData.vbat_flying_percentage |= (*ptr << 24);
 	ptr++;

 	temp = *ptr;
 	ptr++;
 	temp |= (*ptr << 8);
 	ptr++;
 	temp |= (*ptr << 16);
 	ptr++;
 	temp |= (*ptr << 24);
 	ptr++;
 	navdemoData.theta = *(float *)&temp;

 	temp = *ptr;
 	ptr++;
 	temp |= (*ptr << 8);
 	ptr++;
 	temp |= (*ptr << 16);
 	ptr++;
 	temp |= (*ptr << 24);
 	ptr++;
 	navdemoData.phi = *(float *)&temp;

 	temp = *ptr;
 	ptr++;
 	temp |= (*ptr << 8);
 	ptr++;
 	temp |= (*ptr << 16);
 	ptr++;
 	temp |= (*ptr << 24);
 	ptr++;
 	navdemoData.psi = *(float *)&temp;

 	navdemoData.altitude = *ptr;
 	ptr++;
 	navdemoData.altitude |= (*ptr << 8);
 	ptr++;
 	navdemoData.altitude |= (*ptr << 16);
 	ptr++;
 	navdemoData.altitude |= (*ptr << 24);
 	ptr++;

 	temp = *ptr;
 	ptr++;
 	temp |= (*ptr << 8);
 	ptr++;
 	temp |= (*ptr << 16);
 	ptr++;
 	temp |= (*ptr << 24);
 	ptr++;
 	navdemoData.vx = *(float *)&temp;

 	temp = *ptr;
 	ptr++;
 	temp |= (*ptr << 8);
 	ptr++;
 	temp |= (*ptr << 16);
 	ptr++;
 	temp |= (*ptr << 24);
 	ptr++;
 	navdemoData.vy = *(float *)&temp;

 	temp = *ptr;
 	ptr++;
 	temp |= (*ptr << 8);
 	ptr++;
 	temp |= (*ptr << 16);
 	ptr++;
 	temp |= (*ptr << 24);
 	ptr++;
 	navdemoData.vz = *(float *)&temp;

 	navdemoData.num_frames = *ptr;
 	ptr++;
 	navdemoData.num_frames |= (*ptr << 8);
 	ptr++;
 	navdemoData.num_frames |= (*ptr << 16);
 	ptr++;
 	navdemoData.num_frames |= (*ptr << 24);
 	ptr++;

 	//skip over all the other junk for right now
 	ptr += 104;
 }

 void parse_checksum(uint8_t *ptr) {
 	ptr = NULL;
 }
