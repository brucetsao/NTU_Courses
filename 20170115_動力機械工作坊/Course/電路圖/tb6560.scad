lochradius=0.7;
difference() {
	translate([0,0,0]) cube([36, 7*2.56, 1.6], center=true);
	for(i = [0:1:6]) {
		translate([i*2.56,1,0]) cylinder(h=3, r=lochradius, center=true);
	translate([-i*2.56,1,0]) cylinder(h=3, r=lochradius, center=true);
	}
	for(i = [1:1:6]) {
		translate([i*2.56-1.27,-1,0]) cylinder(h=3, r=lochradius, center=true);
	translate([-i*2.56+1.27,-1,0]) cylinder(h=3, r=lochradius, center=true);
	}
	for(i = [0:1:6]) {
		translate([i*2.56,3*2.56,0]) cylinder(h=3, r=lochradius, center=true);
	translate([-i*2.56,3*2.56,0]) cylinder(h=3, r=lochradius, center=true);
	}
	for(i = [1:1:6]) {
		translate([i*2.56,-3*2.56,0]) cylinder(h=3, r=lochradius, center=true);
	translate([-i*2.56,-3*2.56,0]) cylinder(h=3, r=lochradius, center=true);
	}
	for(i = [0:1:6]) {
		translate([i*2.56,1.5*2.56,0]) cylinder(h=3, r=lochradius, center=true);
	translate([-i*2.56,1.5*2.56,0]) cylinder(h=3, r=lochradius, center=true);
	}
	for(i = [1:1:6]) {
		translate([i*2.56,-1.5*2.56,0]) cylinder(h=3, r=lochradius, center=true);
	translate([-i*2.56,-1.5*2.56,0]) cylinder(h=3, r=lochradius, center=true);
	}
}