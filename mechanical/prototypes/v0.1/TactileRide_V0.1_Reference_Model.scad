// TactileRide V0.1 reference model
// STATIC ERGONOMIC PROTOTYPE ONLY - NOT ROAD READY
// All dimensions in millimetres.

$fn = 64;
case_w = 58.0;
case_h = 44.0;
case_d = 26.0;
corner_r = 7.0;
wall = 2.4;
bar_d = 22.2;
clamp_id = 22.5;
clamp_od = 34.5;
clamp_width = 16.0;

module rounded_box(size=[10,10,10], r=2) {
    hull() {
        for (x=[r, size[0]-r])
            for (y=[r, size[1]-r])
                translate([x,y,0]) cylinder(h=size[2], r=r);
    }
}

module front_shell() {
    difference() {
        rounded_box([case_w,case_h,case_d], corner_r);
        translate([wall,wall,wall])
            rounded_box([case_w-2*wall,case_h-2*wall,case_d-wall+0.1], max(1,corner_r-wall));
        // USB-C service opening on right edge
        translate([case_w-wall-0.2,16,5]) cube([wall+1,12,7]);
    }
}

module buttons() {
    // Volume rocker
    translate([3.75,6.5,case_d])
        rounded_box([11.5,31.0,2.2],3.2);
    // Play/pause
    translate([31.0,22.0,case_d]) cylinder(h=2.2,r=9.0);
    // Next and previous paddles
    for (p=[[48.0,33.0],[48.0,11.0]])
        translate([p[0]-9.0,p[1]-5.25,case_d]) rounded_box([18.0,10.5,2.2],2.5);
}

module clamp_ring() {
    difference() {
        rotate([0,90,0]) cylinder(h=clamp_width,r=clamp_od/2);
        translate([-0.1,0,0]) rotate([0,90,0]) cylinder(h=clamp_width+0.2,r=clamp_id/2);
        // split at bottom
        translate([-1,-3,-clamp_od/2-1]) cube([clamp_width+2,6,clamp_od+2]);
    }
}

module ergonomic_mockup() {
    color("dimgray") front_shell();
    color("lightgray") buttons();
}

// Default preview: controller plus detached clamp reference.
ergonomic_mockup();
translate([case_w+20,case_h/2,clamp_width]) rotate([0,0,90]) color("gray") clamp_ring();
