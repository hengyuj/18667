function accel=calculate_acceleration(clutch, speed, accelerator, gear, brake)

%arguments:
%clutch: 0: clutch is realsed
%        1: clutch is pressed
%speed: current car speed
%accelerator:   0: accelerator pedal relased
%               0-5: in between
%               5: accelerator pedal fully pressed
%gear: which gear is currently used by the transmission
%brake: the brake state
%slope: the slope of the terrain

GEARMIN = [-10 10 30];
GEARMAX = [30 50 70];
GEARMID = (GEARMIN+GEARMAX)/2;
GEARSPAN = GEARMID - GEARMIN;

%ACCURACY = 10;
%BRAKE_EFF = 0.1;

SCALE = 10;
BRAKE_EFF = 0.1;

if speed < GEARMID(gear)
    accel = accelerator*(speed - GEARMIN(gear))/GEARSPAN(gear)/SCALE;
else
    accel = accelerator*(GEARMAX(gear) - speed)/GEARSPAN(gear)/SCALE;
end

if clutch == 1
    accel = 0;
end

%Now consider the situation when the brake is pressed
accel = accel - brake*BRAKE_EFF;

