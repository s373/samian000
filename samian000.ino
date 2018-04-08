/*

samian 000.2018.265701

multipurpose lightweight fast firmware,
3 servos (000) 2018.265701 version

                              .cok00ddo'
   .                  .dx0KXXXWMMMMMNKKK'
  'l                  .0MMMMMWWMMMMMN:,,       ,:dl;,.
  'x                   lWMMX0NKKNO0X0        cX0dXWXWKo.
  :0.                  .oOXMMMWNKNWWN.      .oXo::xXXOkl.
  ;N.                   .dXWWWWWWMMMMXccxckx:oOdcccc:::::
  .Nd                 .lKWMMMMMMMMMMMMOXWNxxK0koO0d:lxc;
   l0.               'kXWMMMMMMMMWKMMMKNWWMWKXWKkOKOl;.
   .Wc             .lKWWMMMMMMMWXXWMMMKXMMMMMMMWW0oo;
    oX.            ;KWMMMMMMMW0XMMMMMWXKMMMWWWWKl
    .WO'           dWMMMMMMMXXWMMMMMMMXKWMMMMM0'
     cWNOc..     .kNMMMMMMMWMMMMMMMWWMWWMMMMMK'
      .XMMWKxl,.;XMMMMMMMWMMMMMMMMk.'OKMMNWMN'
       'dKWMMMMWWMMWNkkONMMMMMMMX:    ;NMMWMWO,
          .:kXWNX0,   .oXMMMMM0'       'OWMMMMWKl;oxo,..
                       ;WMMMMWd:,...     ;k00Kk'  ..
                        lxkxdol;....


samian 000 mit license (c) 2009,2014,2018 s373.net/x art codex studios
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


machine builds
        2009
          http://andre-sier.com/uunniivveerrssee/32-bitDifferenceMachine/
        2014
          http://s373.net/x/inky/
        2015
          http://andre-sier.com/piantadelmondo/DMZ/
        2015
          http://andre-sier.com/projects/portrait-machine/
        2015
          http://andre-sier.com/piantadelmondo/Anthemusa/

*/

const unsigned char samian[] = {'s', 'a', 'm', 'i', 'a', 'n', '0', '0', '0', '.',
                                '2', '0', '1', '8', '.',
                                '2', '6', '5', '7', '0', '1'
                               };
#define baud (38400)
#define sdel (10)
#define z0 (93)
#define z1 (93)
#define z2 (20)

// val val val ,
// inky 2009.1723413 serial protocol
int readhead = 0;
int buffervals[4] = { 0, 0, 0, 0 };
int readvals[4] = { 0, 0, 0, 0 };
int readvalsold[4] = { 0, 0, 0, 0 };
// pins
int p0 = 9;
int p1 = 10;
int pz = 11;
#include <Servo.h>
Servo servoo, servom, servoz;


void setup() {

  Serial.begin(baud);

  servoo.attach(p0);
  servom.attach(p1);
  servoz.attach(pz);
  zero();
  establishcontact();

}


void loop() {

  delay(0);

  while (Serial.available() > 0) {
    int incoming = Serial.read();
    buffervals[readhead] = incoming ;

    readhead++;
    if (readhead > 3) {
      readhead = 0;
    }


    // @echo
    Serial.write(incoming);

	if (incoming == 44) { // got a msg


	                                  //scan for terminator
	                                  int comma = -1;
	                                  for (int i = 3; i > -1; i--) {
	                                    if (buffervals[i] == 44) {
	                                      comma = i;
	                                      break;
	                                    }
	                                  }


        if (comma >= 0) {

                for (int i = 0; i < 3; i++) {
                    int el = (comma + 1 + i) % 4;
                    readvals[i] = buffervals[el];
                }


                if (readvalsold[0] != readvals[0]) {
                  readvalsold[0] = readvals[0];
                  writeoservo(readvals[0]);
                }
                if (readvalsold[1] != readvals[1]) {
                  readvalsold[1] = readvals[1];
                  writemservo(readvals[1]);
                }
                if (readvalsold[2] != readvals[2]) {
                  readvalsold[2] = readvals[2];
                  writezservo(readvals[2]);
                }

         }

	}

}}

void zero() {  writeoservo(z0);  writemservo(z1);  writezservo(z2); }
void writeoservo(int v) { servoo.write(v); delay(sdel); }
void writemservo(int v) { servom.write(v); delay(sdel); }
void writezservo(int v) { servoz.write(v); delay(sdel); }
void establishcontact() { int t = 0;
  Serial.println("samian 000");
  while (Serial.available() <= 0) {
    Serial.write(samian[t++]);  // send a capital a
    if (t == 21) { t = 0; Serial.write(10); }
    delay(100);
  }
  Serial.print("samian rx: ");
  while (Serial.available() > 0) { Serial.print(Serial.read()); }
  Serial.println(); for(int i=0; i<21; i++)Serial.print(samian[i]);
  Serial.println(); readhead = 0;
}
