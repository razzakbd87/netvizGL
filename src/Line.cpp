//
// Created by werl on 29/09/16.
//

#include "../inc/Line.h"

Line::Line(GLdouble X1, GLdouble Y1, GLdouble Z1, GLdouble X2, GLdouble Y2, GLdouble Z2) {
    vertices = new GLdouble[6];
    vertices[0] = X1 *.1;
    vertices[1] = Y1 *.1;
    vertices[2] = Z1 *.1;
    vertices[3] = X2 *.1;
    vertices[4] = Y2 *.1;
    vertices[5] = Z2 *.1;
}

Line::~Line() {
    delete vertices;
}

void Line::draw() {
    static GLfloat colors2[] = {1,0,1,
                                0,0,0};

    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, colors2);

    glVertexPointer(3, GL_DOUBLE, 0, this->vertices);

    glPushMatrix();
    glDrawArrays(GL_LINES, 0, 2);
    glPopMatrix();

    glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
    glDisableClientState(GL_COLOR_ARRAY);
}