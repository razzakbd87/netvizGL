//
// Created by werl on 23/09/16.
//

#include "../inc/Point.h"

Point::Point(float OFFSETX, float OFFSETY, float OFFSETZ) {

    offsetX = OFFSETX, offsetY = OFFSETY, offsetZ = OFFSETZ;
    colourR = 0, colourB = 0, colourG = 0;

    const GLfloat RINGS = (float) 1.0 / (rings - 1);
    const GLfloat SECTORS = (float) 1.0 / (sectors - 1);

    int r, s, vertIndex = 0, colIndex = 0;
    indIndex = 0;

    vertices = new GLdouble[rings * sectors * 3];
    colours = new GLdouble[rings * sectors * 3];

    for (r = 0; r < rings; r++) {
        for (s = 0; s < sectors; s++) {

            GLdouble x = offsetX + cos(2 * M_PI * s * SECTORS) * sin(M_PI * r * RINGS);
            GLdouble y = offsetY + sin(-M_PI_2 + M_PI * r * RINGS);
            GLdouble z = offsetZ + sin(2 * M_PI * s * SECTORS) * sin(M_PI * r * RINGS);

            vertices[vertIndex++] = x * radius;
            vertices[vertIndex++] = y * radius;
            vertices[vertIndex++] = z * radius;

            colours[colIndex++] = colourR;
            colours[colIndex++] = colourG;
            colours[colIndex++] = colourB;
        }
    }

    indices = new GLuint[rings * sectors * 4];

    for (r = 0; r < rings - 1; r++)
        for (s = 0; s < sectors - 1; s++) {

            indices[indIndex++] = r * sectors + s;
            indices[indIndex++] = r * sectors + (s + 1);
            indices[indIndex++] = (r + 1) * sectors + (s + 1);
            indices[indIndex++] = (r + 1) * sectors + s;

        }
}

void Point::draw() {

    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColorPointer(3, GL_DOUBLE, 0, colours);

    glVertexPointer(3, GL_DOUBLE, 0, this->vertices);

    glPushMatrix();
    glDrawElements(GL_QUADS, this->indIndex, GL_UNSIGNED_INT, this->indices);
    glPopMatrix();

    glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
    glDisableClientState(GL_COLOR_ARRAY);

    if (line != NULL){
        line->draw();
    }
}

Point::~Point() {

}

void Point::setColour(GLdouble R, GLdouble G, GLdouble B) {

    colourR = R;
    colourG = G;
    colourB = B;

    int colIndex = 0;

    for (int r = 0; r < rings; r++) {
        for (int s = 0; s < sectors; s++) {
            colours[colIndex++] = colourR;
            colours[colIndex++] = colourG;
            colours[colIndex++] = colourB;
        }
    }
}

GLdouble *Point::getColour() {
    GLdouble *ret = new GLdouble[3];
    ret[0] = colourR;
    ret[1] = colourG;
    ret[2] = colourB;
    return ret;
}

void Point::attachPoint(Point *p) {
    attachedPoint = p;
    line = new Line(offsetX * 0.1,offsetY * 0.1,offsetZ * 0.1,
                    p->offsetX * 0.1,p->offsetY * 0.1,p->offsetZ * 0.1);
}