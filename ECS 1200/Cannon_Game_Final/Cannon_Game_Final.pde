 //Cannon Game
//
//Created By: Daniel Eisterhold

import ddf.minim.*;
Minim minimplay; 
AudioSnippet winner, loser, background;
boolean newTarget = false;

boolean pause = false;
boolean fire = false;
boolean gameOver = false;
int attempts = 0;
int hit = 0;
int miss = 0;
int level=1;
int health=1;
int total_attempts = 10;
int final_attempts;
int max_health=level;
class Cannon
{
  float oldXPos;
  float oldYPos;
  float xPos;
  float yPos;
  int firingAngle;
  int currentAngle;
  int cannonAngle;
  final float gravity = 32;
  final float velocity = width/5;
  final float timeModifier = .05;
  float currentTime;
  String status = "Waiting...";
  PImage Projectile;
  PImage Cannon;
  PImage Target;
  int targetWidth = 50;
  int targetHeight = 50;
  float targetXPos = 0;
  int targetAlpha = 255;
  color bg = color(27, 171, 51);
  Cannon()
  {
  xPos = 0;
  yPos = 0;
  oldXPos = 0;
  oldYPos = 0;
  currentAngle = 45;
  cannonAngle = 45;
  currentTime = 0;
  Projectile = loadImage("Projectile.png");
  Cannon = loadImage("Cannon.png");
  Target = loadImage("Target.png");
  targetWidth = 50;
  targetHeight = 50;
  targetXPos = random(width/3,width-targetWidth);
  }
  
  void drawCannon()
  {
    //println("Drawing Cannon");
    //    println("Fire Status "+fire);
    pushMatrix();
    translate(5,height-30);
    stroke(#ffffff);
    fill(#ffffff);
    ellipse(0,0,150,150);
    rotate(radians(cannonAngle)*-1);
    fill(#ffffff);
    rect(-3,-3,60,30);
    image(Cannon,0,0,54,24);
    popMatrix(); 
  }
  
  void drawProjectile()
  {
    //println("Drawing Projectile");
    //println("Fire Status "+fire);
    status = "Running...";
    oldXPos = xPos;
    oldYPos = yPos;
    xPos = velocity*currentTime*cos(radians(firingAngle));
    yPos = height-((velocity*currentTime*sin(radians(firingAngle)))-(.5*gravity*(sq(currentTime))));
    currentAngle = int(-1*degrees(atan(((yPos-oldYPos)/(xPos-oldXPos)))));
    println(currentAngle);
    drawCannon();
    pushMatrix();
    translate(xPos,yPos);
    rotate(radians(currentAngle)*-1);
    fill(#ffffff);
    stroke(#ffffff);
    image(Projectile,-40,-7.5,45,15);
    popMatrix();
  }
  
  void increaseCannonAngle()
  {
    if(cannonAngle < 90)
    {
      cannonAngle += 1;
    }
    else
    {
      cannonAngle = 90;
    }
    this.drawCannon();
    this.drawInformation();
  }
  
  void decreaseCannonAngle()
  {
    if(cannonAngle>1)
    {
      cannonAngle -= 1;
    }
    else
    {
      cannonAngle = 0;
    }
    this.drawCannon();
    this.drawInformation();
  }
  
  void setAngle()
  {
    firingAngle = cannonAngle;
  }
  
  void drawInformation()
  {
    //println("Fire Status "+fire);
    //println("Drawing Info");
    fill(#ffffff);
    stroke(#ffffff);
    rect(0,0,200,180);
    fill(#000000);
    text("X-Pos: "+nf(int(xPos),3)+"  Y-Pos: "+nf(int(yPos),3),10,20);
    text("Current Time: "+nf(currentTime,2,2),10,40);
    text("Cannon Angle: "+cannonAngle,10,60);
    text("Number of Attempts: "+attempts,10,80);
    text("Number of Attempts Left: "+final_attempts,10,100);
    text("Hits: "+hit+" Misses: "+miss,10,120);
    text("Status: "+status,10,140);
    text("Level:"+level+" Health:"+health,10,160);
    println("Fire Status "+fire);
  }
  
  void randomizeTarget()
  {
    targetXPos = random(width/3,width-targetWidth);
  }
  void drawTarget()
  {
    if(!newTarget)
    {
    fill(bg);
    println("Drawing Target");
    ellipseMode(CENTER);
    ellipse(targetXPos,height,targetWidth,targetHeight);
    }
    else
    {
      fill(bg);
      println("Drawing New Target");
      imageMode(CORNER);
      //println("Transparency: "+targetAlpha);
      tint(255,targetAlpha);
      image(Target,targetXPos-25,height-64,50,64);

      draw();
    }
  }
  
  boolean checkTarget()
  {
    attempts++;
    float distance = dist(targetXPos,height,xPos,yPos);
    println(targetXPos);
    println("X Pos: "+xPos);
    println(targetXPos+targetWidth);
    if(distance <=targetWidth+5 && distance <=targetHeight/2)
    {
      winner.rewind();
      winner.play();
      setup();
      targetAlpha -= 64;
      return true;
    }
    else
    {
      loser.rewind();
      loser.play();
      return false;
    }
  }
  
  float maxTime()
  {
    float maxTime = ((2*velocity*sin(radians(firingAngle)))/gravity);
    return maxTime;
  }
  
  float currentTime()
  {
    return currentTime;
  }
  
  void incrementTime()
  {
    currentTime += timeModifier;
  }
  
  void setStatus(String currentStatus)
  {
    status = currentStatus;
    println("Changing status to "+currentStatus);
    myCannon.drawInformation();
  }
  
  void reset()
  {
    xPos = 0;
    yPos = 0;
    fire = false;
    currentTime = 0;
    status = "Waiting...";
    drawCannon();
    drawInformation();  
  }

void change_color(int value) {
    switch (value){
     case 1:
             bg= color(146, 255, 89);
             break; 
      case 2:
            println(2);
             switch(health){
                 case 1:
                        bg= color(225, 128, 0);
                        break;
                 case 2: 
                        bg= color(146, 255, 89);
                       break; 
             }
             break; 
      case 3:
            switch(health){
                 case 1:
                        bg= color(155, 17, 9);
                        break;
                 case 2:
                        bg= color(231, 149, 74); //orange
                        break;
                 case 3: 
                        bg= color(146, 255, 89);
                       break; 
             }
             break; 
      case 4:
            switch(health){
                 case 1:
                        bg= color(155, 17, 9);
                        break;
                 case 2:
                        bg= color(231, 149, 74); //orange
                        break;
                 case 3:
                        bg= color(254, 251, 89); //yellow
                        break;
                 case 4: 
                        bg= color(146, 255, 89);
                       break; 
             }
             break; 
      case 5:
            switch(health){
                 case 1:
                       bg= color(155, 17, 9); //red
                        break;
                 case 2:
                       bg= color(231, 149, 74); //orange
                        break;
                 case 3:
                        bg= color(254, 251, 89); //yellow
                        break;
                 case 4: 
                        bg= color(78, 134, 54); //dark green
                        break;
                 case 5: 
                        bg= color(146, 255, 89);
                       break; 
             }
             break; 
    }
}
  void got_hit() {
    if(level==1){
        health--;
    }
    if (health==0) {
      level++;
      this.reset_health();
    }
    else {
      health--;
      change_color(level);
      if(health==0){
        level++;
         this.reset_health(); 
      }
    }
  }
  void reset_health() {
    health = level;
    max_health=level;
  }
}


//Declare Cannon Object
Cannon myCannon;

void setup()
{
  println("Inside Setup");
  size(800,400);//Initialize Window
  //frame.setResizable(false);
  myCannon = new Cannon(); //Initialize myCannon
  minimplay = new Minim(this); //Initialize Sound Player
  loser = minimplay.loadSnippet("loser.mp3");
  winner = minimplay.loadSnippet("winner.wav");
  background = minimplay.loadSnippet("background.wav");
  background(#ffffff); //Set Background to White
  myCannon.drawCannon();
  myCannon.drawInformation();
  myCannon.randomizeTarget();
  myCannon.drawTarget();
  background.rewind();
  background.play();
}

void draw()
{
  final_attempts = total_attempts - attempts;
  if (final_attempts <= 0){
    final_attempts = 0;
    myCannon.drawInformation();
    fire = false;
    gameOver = true;
    fill(255);
    rect(150,150,120,40);
    fill(0);
    stroke(0);
    text("You Lose!", 150,150);
    noLoop();
  }
  if(fire && !gameOver)
  {
    //println("Fire Status "+fire);
    background(#ffffff);
    myCannon.drawTarget();
    //println("Fire Status "+fire);
    myCannon.drawInformation();
    //println("Running");
    myCannon.drawProjectile();
    myCannon.drawCannon();
    myCannon.incrementTime();
    //println("Fire Status "+fire);
  }
  if(myCannon.currentTime() > myCannon.maxTime())
    {
      //println("Projectile has landed.");
      if(myCannon.checkTarget())
      {
        hit++;
        text("You Win!", width/2,height/2);
        noLoop();
        myCannon.got_hit();
        myCannon.drawTarget();
      }
      else
      {
        text("You Miss!", width/2,height/2);
        miss++;
      }
      myCannon.reset();
      myCannon.drawInformation();
    }
  //println(fire);
  
}

void keyPressed()
{
  if (key == CODED)
  {
    if(keyCode == UP || keyCode == LEFT)
    {
    println("Up Key Pressed");
    myCannon.increaseCannonAngle();
    }
    else if (keyCode == DOWN || keyCode == RIGHT)
    {
    println("Down Key Pressed");
    myCannon.decreaseCannonAngle(); 
    }
  }
  
  if (key == ' ')
  {
    println("Space Key Pressed");
    if(!fire)
    {
      fire = true;
      myCannon.setAngle();
    }
  }
  else if (key == 'p')
  {
    println("Pause Game");
    pause = !pause;
  }
  else if (key == 'q')
  {
    println("Game Quitting");
    exit();
  }
  else if (key == 'r')
  {
    println("Resetting Game");
    health=1;
    level=1;
    pause = false;
    setup();
  }
  else if (key == 't')
  {
    newTarget = true;
    myCannon.drawTarget();
  }
  if(pause)
  {
    myCannon.setStatus("Paused...");
    noLoop();
  }
  else
  {
    loop();
  }
}
