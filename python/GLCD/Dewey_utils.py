# Dewey_utils.py
# Python module of custom utility functions
# Fayetteville Free Library Robotics Club
# June 2016, Bob Lawler

# ----- GENERAL -----

def clamp(n, minn, maxn):	# Clamp value (n) within range
	return(min(max(minn,n),maxn))
	
