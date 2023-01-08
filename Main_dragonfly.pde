Dragonfly body; // Dragonfly class => body objet

void setup() 
{
  size(1000, 500);
	body = new Dragonfly(width*3/10, height/2); //assiging the body position to the position vector using the Dragonfly class
}

void draw() 
{
  background(255); 
	
	body.display();
	
	body.flap();
	body.loop();
	
	PVector gravity = new PVector(0, 0.15);
  body.applyForce(gravity); // adds the gravity vector to ball
	body.update(); // Updates Dragonfly body position values 
}