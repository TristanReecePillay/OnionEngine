#include "SphereGameObject.h"
#include <GL/freeglut.h>

void SphereGameObject::drawGeometry() {
    glColor3f(1, 1, 1);
    glutSolidSphere(0.5f, 12, 12);
}