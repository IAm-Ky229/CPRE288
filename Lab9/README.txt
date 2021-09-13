Function Logic Tree

We are currently in range
	Is the last angle 0?
		Yes
			We make a new object (FIN)
		No 
			Last angle is an object
				New angle is within tolerance
					Do nothing (FIN)
				New angle is not within tolerance
					Make a new object and end the last object (FIN)
			Last angle is not an object
				We make a new object (FIN)

We are currently not in range
	Last angle was in range
		Make end of object (FIN)
	Last angle was not in range
		Do nothing (FIN)
