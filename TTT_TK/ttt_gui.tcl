#  Create the main message window
wm title . "TicTacToe in TCL!" 
#Set dimensions of the TicTacToe box size                       
wm geometry . 210x210+300+300     
#Variable used to draw                    
canvas .can                                                                 

#consumes a gif files and saves it to a variable 
set cross [image create photo -file ./cross.gif]    
set not [image create photo -file ./not.gif]
# Updates the GUI based on the following integer code values
# 100 : places X in coordinate (0,0)
# 101 : places X in coordinate (0,1)
# 102 : places X in coordinate (0,2) 
# 110 : places X in coordinate (1,0)
# 111 : places X in coordinate (1,1)
# 112 : places X in coordinate (1,2)
# 120 : places X in coordinate (2,0)
# 121 : places X in coordinate (2,1)
# 122 : places X in coordinate (2,2)
# 200 : places O in coordinate (0,0)
# 201 : places O in coordinate (0,1)
# 202 : places O in coordinate (0,2) 
# 210 : places O in coordinate (1,0)
# 211 : places O in coordinate (1,1)
# 212 : places O in coordinate (1,2)
# 220 : places O in coordinate (2,0)
# 221 : places O in coordinate (2,1)
# 222 : places O in coordinate (2,2)
# 30 : clears the screen
proc updater {code} {
	global cross
	global not
	switch $code {
		100 {
 			.can create image 40 40 -image $cross
			pack .can	 
		}
		101 {
 			.can create image 105 40 -image $cross
			pack .can	 
		}
		102 {
 			.can create image 170 40 -image $cross
			pack .can	 
		}
		110 {
 			.can create image 40 105 -image $cross
			pack .can	 
		}
		111 {
 			.can create image 105 105 -image $cross
			pack .can	 
		}
		112 {
 			.can create image 170 105 -image $cross
			pack .can	 
		}
		120 {
 			.can create image 40 170 -image $cross
			pack .can
		}	 
		121 {
 			.can create image 105 170 -image $cross
			pack .can
		}	 
		122 {
 			.can create image 170 170 -image $cross
			pack .can	 
		}
		200 {
 			.can create image 40 40 -image $not
			pack .can	 
		}
		201 {
 			.can create image 105 40 -image $not
			pack .can	 
		}
		202 {
 			.can create image 170 40 -image $not
			pack .can	 
		}
		210 {
 			.can create image 40 105 -image $not
			pack .can	 
		}
		211 {
 			.can create image 105 105 -image $not
			pack .can	 
		}
		212 {
 			.can create image 170 105 -image $not
			pack .can	 
		}
		220 {
 			.can create image 40 170 -image $not
			pack .can
		}	 
		221 {
 			.can create image 105 170 -image $not
			pack .can
		}	 
		222 {
 			.can create image 170 170 -image $not
			pack .can	 
		}
		30 {
			.can delete "all"
			.can create rect 10 10 200 200
			.can create line 70 10 70 200
			.can create line 140 10 140 200
			.can create line 10 70 200 70
			.can create line 10 140 200 140
			pack .can
		}	
		default {
		}
	}
}

# Creates the TicTacToe Grid
.can create rect 10 10 200 200    
.can create line 70 10 70 200
.can create line 140 10 140 200
.can create line 10 70 200 70   
.can create line 10 140 200 140 
pack .can
                
proc read_stdin {} {                           
    gets stdin x
    updater $x
}             
#Connects the triggering of the stdin to the read_stdin procedure                        
fileevent stdin readable read_stdin            
