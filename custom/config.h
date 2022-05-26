#ifndef CFG_H
#define CFG_H

/*单位
角度：°
转速：rpm
电流：A
转矩：N·m
时间：ms
频率：Hz

*/

#define task_period 2
#define zeromotoranglespeed  30.f
#define maxanglespeed 500.f
#define maxcurrentvalue 10000.f
#define maxcurrent 10.f
#define reductionratio 36.f
#define maxfingerangle 230.f
#define minfingerangle -230.f
#define maxpalmangle 460.f 
#define minpalmangle -460.f
#define maxpalmdifangle 0.f
#define safecurrentcoe 0.4f
#define tccoe 3.f
#define ctcoe 1.f/tccoe

#define tp task_period 
#define zas zeromotoranglespeed  
#define maxas maxanglespeed 
#define maxfa maxfingerangle
#define minfa minfingerangle
#define maxpa maxpalmangle
#define minpa minpalmangle


#define finger1_default_config \
{ \
	{ \
		{minfa,maxfa}, \
		maxas, \
		{maxcurrentvalue,maxcurrent}, \
		ctcoe, \
		reductionratio, \
		0.f, \
		0.f, \
		2, \
		0x1,\
		-1,\
		1,\
	}, \
	{ \
		0.f, \
		0.f, \
		0.f, \
		0.f, \
		0.f, \
		{0.f,0.f}, \
	}, \
	{ \
		0.f, \
		0.f, \
		0.f, \
	}, \
	{ \
		0.f, \
		0.f, \
		{0.f,0.f,0.f,0.f,0.f}, \
	}, \
} \

#define finger2_default_config \
{ \
	{ \
		{minfa,maxfa}, \
		maxas, \
		{maxcurrentvalue,maxcurrent}, \
		ctcoe, \
		reductionratio, \
		0.f, \
		0.f, \
		2, \
		0x1,\
		-1,\
		1,\
	}, \
	{ \
		0.f, \
		0.f, \
		0.f, \
		0.f, \
		0.f, \
		{0.f,0.f}, \
	}, \
	{ \
		0.f, \
		0.f, \
		0.f, \
	}, \
	{ \
		0.f, \
		0.f, \
		{0.f,0.f,0.f,0.f,0.f}, \
	}, \
} \

#define palm1_default_config \
{ \
	{ \
		{minpa,maxpa}, \
		maxas, \
		{maxcurrentvalue,maxcurrent}, \
		ctcoe, \
		reductionratio, \
		0.f, \
		0.f, \
		2, \
		0x1,\
		-1,\
		1,\
	}, \
	{ \
		0.f, \
		0.f, \
		0.f, \
		0.f, \
		0.f, \
		{0.f,0.f}, \
	}, \
	{ \
		0.f, \
		0.f, \
		0.f, \
	}, \
	{ \
		0.f, \
		0.f, \
		{0.f,0.f,0.f,0.f,0.f}, \
	}, \
} \

#define palm2_default_config \
{ \
	{ \
		{minpa,maxpa}, \
		maxas, \
		{maxcurrentvalue,maxcurrent}, \
		ctcoe, \
		reductionratio, \
		0.f, \
		0.f, \
		2, \
		0x1,\
		1,\
		-1,\
	}, \
	{ \
		0.f, \
		0.f, \
		0.f, \
		0.f, \
		0.f, \
		{0.f,0.f}, \
	}, \
	{ \
		0.f, \
		0.f, \
		0.f, \
	}, \
	{ \
		0.f, \
		0.f, \
		{0.f,0.f,0.f,0.f,0.f}, \
	}, \
} \

#define finger_angle_pid \
{ \
	0.f, \
	0.f, \
	{0.f,0.f}, \
	0.f, \
	0.f, \
	0.f, \
	0.f, \
	0.f, \
	0.f, \
	zeromotoranglespeed, \
	zeromotoranglespeed, \
	zeromotoranglespeed, \
	0.f, \
	zeromotoranglespeed, \
} \

#define finger_speed_pid \
{ \
	0.f, \
	0.f, \
	{0.f,0.f}, \
	0.f, \
	0.f, \
	0.f, \
	0.f, \
	0.f, \
	0.f, \
	safecurrentcoe*maxcurrentvalue, \
	safecurrentcoe*maxcurrentvalue, \
	safecurrentcoe*maxcurrentvalue, \
	0.f, \
	safecurrentcoe*maxcurrentvalue, \
} \

#define palm_angle_pid \
{ \
	0.f, \
	0.f, \
	{0.f,0.f}, \
	0.f, \
	0.f, \
	0.f, \
	0.f, \
	0.f, \
	0.f, \
	zeromotoranglespeed, \
	zeromotoranglespeed, \
	zeromotoranglespeed, \
	0.f, \
	zeromotoranglespeed, \
} \

#define palm_speed_pid \
{ \
	0.f, \
	0.f, \
	{0.f,0.f}, \
	0.f, \
	0.f, \
	0.f, \
	0.f, \
	0.f, \
	0.f, \
	safecurrentcoe*maxcurrentvalue, \
	safecurrentcoe*maxcurrentvalue, \
	safecurrentcoe*maxcurrentvalue, \
	0.f, \
	safecurrentcoe*maxcurrentvalue, \
} \





#endif
