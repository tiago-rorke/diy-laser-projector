import oscP5.*;
import netP5.*;

OscP5 oscP5;
NetAddress server;

OscBundle msg = new OscBundle();
OscMessage msg_x = new OscMessage("/X");
OscMessage msg_y = new OscMessage("/Y");
OscMessage msg_r = new OscMessage("/R");
OscMessage msg_g = new OscMessage("/G");
OscMessage msg_b = new OscMessage("/B");

String host = "localhost";
int port = 9000;

void setup() {
  size(500,500);
  frameRate(25);

  /* start oscP5, listening for incoming messages at port 12000 */
  oscP5 = new OscP5(this,12000);

  server = new NetAddress(host, port);

  background(150);
  stroke(255);
  noFill();
  beginShape();

}


void draw() {

  // Draw some random dots
/*
  for(int i=0; i<100; i++) {
   laserVertex(random(0,width),random(0,height));
   delay(10);
  }
*/

  // Draw a square
/*
  laserVertex(100,100);
  delay(8);
  laserVertex(100,400);
  delay(8);
  laserVertex(400,400);
  delay(8);
  laserVertex(400,100);
  delay(8);
  */
}


void mousePressed() {
  laserVertex(mouseX, mouseY);
}


void laserVertex(float x, float y) {
  vertex(x,y);
  x = map(x, 0, width, -1.0, 1.0);
  y = map(y, 0, height, 1.0, -1.0);
  laserVertexSend(x,y,1,0,0);
}


void laserVertexSend(int n, float x, float y, int r, int g, int b) {

  msg.clear();

  msg_x.clearArguments();
  msg_y.clearArguments();
  msg_r.clearArguments();
  msg_g.clearArguments();
  msg_b.clearArguments();

  msg_x.add(x);
  msg_y.add(y);
  msg_r.add(r);
  msg_g.add(g);
  msg_b.add(b);

  msg.add(msg_x);
  msg.add(msg_y);
  msg.add(msg_r);
  msg.add(msg_g);
  msg.add(msg_b);

  oscP5.send(msg, server);

}
