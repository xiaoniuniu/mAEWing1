
#include <stdlib.h>
#include <math.h>

#include "../globaldefs.h"
#include "systemid_interface.h"

#include AIRCRAFT_UP1DIR

int overspeed = TRUE;
double overspeed_limit = 2.0; // overspeed threshold [m/s]
int indx;

extern void get_system_id(double time, struct sensordata *sensorData_ptr, struct nav *navData_ptr, struct control *controlData_ptr, struct mission *missionData_ptr){
	
	if (controlData_ptr->ias_cmd < (sensorData_ptr->adData_ptr->ias_filt - overspeed_limit)){
		overspeed = TRUE;
	}
	else{
		overspeed = FALSE;
	}
	
	indx = (int) (time*150.0);
	
	switch(missionData_ptr -> sysid_select){
		case 0: 
			// SysID#1
			
			if (time < 2.0){
			}
			else if((time >= 2.0) && (time < 14.0)){
				controlData_ptr->surf3_excite = playback_OMS1_1(indx - 2.0*150, 6.0*D2R);
				if(overspeed == FALSE) {
					controlData_ptr->l3    += controlData_ptr->surf3_excite;
					controlData_ptr->r3    += controlData_ptr->surf3_excite;
				}
			}
			
			controlData_ptr->cmp_status = time / (14.0) * 100.0;
			break;
		case 1:
			// SysID#2
			
			if (time < 10.0){
			}
			else if((time >= 10.0) && (time < 22.0)){
				controlData_ptr->surf3_excite = playback_OMS1_1(indx - 10.0*150, 6.0*D2R);
				if(overspeed == FALSE) {
					controlData_ptr->l3    += controlData_ptr->surf3_excite;
					controlData_ptr->r3    += controlData_ptr->surf3_excite;
				}
			}
			
			controlData_ptr->cmp_status = time / (22.0) * 100.0;
			break;
		case 2:
			// SysID#3
			
			if (time < 10.0){
			}
			else if((time >= 10.0) && (time < 22.0)){
				controlData_ptr->surf2_excite = playback_OMS2_1(indx - 10.0*150, 6.0*D2R);
				controlData_ptr->surf3_excite = playback_OMS2_2(indx - 10.0*150, 6.0*D2R);
				if(overspeed == FALSE) {
					controlData_ptr->l2    += controlData_ptr->surf2_excite;
					controlData_ptr->r2    += controlData_ptr->surf2_excite;
					controlData_ptr->l3    += controlData_ptr->surf3_excite;
					controlData_ptr->r3    += controlData_ptr->surf3_excite;
				}
			}
			
			controlData_ptr->cmp_status = time / (22.0) * 100.0;
			break;
	}
}
