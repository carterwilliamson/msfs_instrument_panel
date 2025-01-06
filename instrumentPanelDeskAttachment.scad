width=70;
height=10;
depth=3;
holeRadius=3/2;

deskThickness=29.65;
deskDropback=12;

vertDepth=55+deskDropback;
vertWidth=5;
vertHeight=height;

//Main support
translate([-width/2, -height/2,0])
{
    difference(){
        margin=5;
        cube([width, height, depth]);
        
        //Screw holes
        //Left
        translate([margin,margin,-1]){
            cylinder(r=holeRadius, h=depth*2, $fn=32);
        }
        //Right
        translate([width-margin,height-margin,-1]){
            cylinder(r=holeRadius, h=depth*2, $fn=32);
        }
    }
}


//Right vert
translate([(deskThickness/2), -vertHeight/2, 0]){
    cube([vertWidth,vertHeight,vertDepth]);
}

//Left vert
translate([-(deskThickness/2)-(vertHeight/2), -vertHeight/2, 0]){
    cube([vertWidth,vertHeight,vertDepth]);
}


//Inside Bevels
translate([-deskThickness/2,-vertHeight/2,0]){
    difference(){
        cube([deskThickness, vertHeight,10]);
        rotate([90,0,0]){
            translate([15,20,-12]){
                cylinder(r=20,h=vertHeight*2, $fn=32);}
        }
    }
}

//Outside Left Bevel
translate([-deskThickness-20.25,-vertHeight/2,0]){
    difference(){
        cube([deskThickness+2, vertHeight,10]);
        rotate([90,0,0]){
            translate([15,20,-12]){
                cylinder(r=20,h=vertHeight*2, $fn=32);
            }
        }
        
        translate([-5,-1,-1]){
            cube([30,100,100]);
        }
    }
    
                 
}

//Outside Right Bevel
translate([deskThickness-20.25+vertHeight,-vertHeight/2,0]){
    difference(){
        cube([deskThickness, vertHeight,10]);
        rotate([90,0,0]){
            translate([15,20,-12]){
                cylinder(r=20,h=vertHeight*2, $fn=32);  
            }
        }
        
        translate([8,-1,-1]){
            cube([30,100,100]);
        }
    }
    
                 
}
