//
// Created by werl on 23/09/16.
//

#ifndef NETVIZGL_SPHERE_H
#define NETVIZGL_SPHERE_H

#include <cmath>
#include "Line.h"
#include <vector>
#include <mutex>

using namespace std;
class Vertex {
 public:

  static const unsigned int rings = 8, sectors = 8;
  static constexpr double radius = .01;

  vector<Vertex *> attachedPoints;

  void attachPoint(Vertex *p);

  vector<Line *> lines;

  GLdouble colourR;
  GLdouble colourG;
  GLdouble colourB;

  Vertex(GLdouble offsetx, GLdouble offsety, GLdouble offsetz);

  GLdouble posX, posY, posZ;
  GLdouble forceX, forceY, forceZ;
  GLdouble velocityX, velocityY, velocityZ;

  GLuint *indices;
  GLint indIndex;

  virtual ~Vertex();

  void draw();

  void setColour(GLdouble r, GLdouble g, GLdouble b);

  GLdouble *getColour();

  GLdouble *vertices;
  GLdouble *colours;
  void update();

  std::mutex mtx;
};

#endif //NETVIZGL_SPHERE_H
