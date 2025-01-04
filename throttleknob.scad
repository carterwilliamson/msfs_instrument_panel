attachHeight=7;
handleHeight=7;
totalHeight=2*attachHeight;
pegRadius=3;
printerMargin=0.1;
handleCylinderFn=32;
attachCylinderFn=16;
handleTextures=8;
handleTextureRadius=10;
frequency=360/handleTextures;
handleRadius=5;
handleTextureOffset=14;

translate([0,0,handleHeight]){
    difference(){
        cylinder(h=attachHeight, r=pegRadius+2, $fn=attachCylinderFn);


        translate([0,0,-1]){
            difference(){
                cubeCutoutHeight=10;
                cubeCutoutOffset=pegRadius/2;
                attachHeightWithMargin=attachHeight+4;
                
                cylinder(
                    h=attachHeightWithMargin,
                    r=pegRadius+printerMargin,
                    $fn=32
                );
                
                translate([
                    -cubeCutoutHeight/2,
                    cubeCutoutOffset+printerMargin,
                    0
                ]){
                    
                    cube(size=[
                        cubeCutoutHeight,
                        cubeCutoutOffset,
                        attachHeightWithMargin
                    ]);
                }
            }
        }    
    }
}


difference(){
    cylinder(h=attachHeight, r=handleTextureRadius, $fn=handleCylinderFn);
        
    for(i=[0:frequency:360]){
        rotate(i, [0,0,1]){
            handleHeightWithMargin=handleHeight+4;
            
            translate([handleTextureOffset,0,-1]){
                cylinder(
                    h=handleHeightWithMargin, 
                    r=handleRadius, 
                    $fn=handleCylinderFn
                );
            }
        }
    }
}
    
    