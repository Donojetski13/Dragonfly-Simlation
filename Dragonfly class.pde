class Dragonfly 
{
	// data that comprises the Dragonfly Object
	
	PVector position;
  PVector velocity;
  PVector acceleration;
	float topspeed; // speed cap
	// pvectors for the two separte wings //
	PVector wing1;  // positon vector
	PVector wing2;  // positon vector
	
	float angle; // angle for polar oscillation 
	float aVel;
	float aAccel;
	float amplitude; // pixels like radius (might have to relocate)
	float rotation;  // for body row rotation
	float direction;   // for changing the direction of x speed
	
	Dragonfly(float x, float y)
	{
		position = new PVector(x,y); // position 
    velocity = new PVector(0);
    acceleration = new PVector(0);
		
		topspeed = 10;
		
		wing1 = new PVector(18,-80);
		wing2 = new PVector(40,-78);
		
		angle = -PI/2; // Start wings up
		aVel = 0;
		aAccel = PI/4;
		amplitude = 80;
		rotation = 0;
		direction = 1.0;
	}
	
	  void update() // update function
  {  
    velocity.add(acceleration); // accelaration adds to velocity 
    velocity.limit(topspeed); 
    position.add(velocity); // velocity adds to position
    acceleration.mult(0); // acceleration is constant
		
		aVel += aAccel; // accelaration adds to velocity  
    angle += aVel; // velocity adds to position
  }
	
  void applyForce(PVector force) 
	{
    acceleration.add(force);
  }
	
void flap() 
	{
    wing1.y = amplitude * sin(angle);
		wing2.y = amplitude * sin(angle);
		if(sin(angle) >= 1)
		{
			if (position.x > width)
			{
				position.x = width;
				direction = direction * -1;
				PVector adjust = new PVector(-2.9, 0);
				body.applyForce(adjust); 
			}
			if (position.x < 5)
			{
				position.x = 5;
				direction = direction * -1;
				PVector adjust = new PVector(2.9, 0);
				body.applyForce(adjust);
			}
			PVector thrust = new PVector(direction, -1.25);
			body.applyForce(thrust); // adds the thrust vector to dragonfly
		}
  }
	
	void loop() 
	{
		if (position.y > height+height/10)
			position.y = 0;
		else if (position.y < -height/10)
			position.y = height;
  }
	
	void display() 
	{ 
    noStroke(0);
		fill(70);
    pushMatrix(); // code in matrix is isolated from outside code
    translate(position.x,position.y); // Sets center of dragonflys body as center
		if (direction < 0)
		{
			rotation = -PI/4; // backward rotation
		} else
			rotation = PI/18;// forward rotation 
		
		rotate(rotation);   

    rectMode(CENTER);
		rect(0,0,30,10);         // Dragonfly body
		ellipse(-55,0,110,15);
		ellipse(10,0,26,20);
		ellipse(36,-5,40,30);
		rect(56,-3,10,10);
		ellipse(67,-7,19,30);    //  ^^^^
		// design for the two wings //
		rotate(-PI*2/12);
		fill(0, 50);
		ellipse(wing1.x,wing1.y,20,20);
		ellipse(wing2.x,wing2.y,20,20);
		stroke(30, 100);
		strokeWeight(20);
		line(23,-9,wing1.x,wing1.y);
		line(40,-8,wing2.x,wing2.y);
    popMatrix(); // 
  }
}