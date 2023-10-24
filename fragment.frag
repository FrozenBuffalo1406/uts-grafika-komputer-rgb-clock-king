#version 330

uniform float currentSecondPointer;
uniform float currentMinutePointer;
uniform float currentHourPointer;

uniform vec4 color1;
uniform vec4 color2;
uniform vec4 color3;

layout (location = 0) out vec4 color;
varying vec2 vPos;

void main()
{
	color = vec4(1.0, 1.0, 1.0, 1.0);
	
	float distance = length(vPos);

	if (distance <= 0.8)
	{
		color = vec4(1.0, 1.0, 1.0, 1.0);
	}

	//drawing second
	float dotSecond = dot(normalize(vPos), vec2(cos(currentSecondPointer), sin(currentSecondPointer)));
	if (distance >= 0.3 && distance <= 0.35 && dotSecond < sin(currentSecondPointer))
	{
			color = color3;
	}

	//drawing minute
	float dotMinute = dot(normalize(vPos), vec2(0.6 * cos(currentMinutePointer), 0.6 * sin(currentMinutePointer)));
	if (distance >= 0.4 && distance <= 0.5 && dotMinute < 0.6 * sin(currentMinutePointer))
	{
		color = color2;
	}

	//drawing hour
	float dotHour = dot(normalize(vPos), vec2(0.8 * cos(currentHourPointer), 0.8 * sin(currentHourPointer)));
	if (distance >= 0.55 && distance <= 0.8 && dotHour < 0.8 * sin(currentHourPointer))
	{
		color = color1;	
	}
}
