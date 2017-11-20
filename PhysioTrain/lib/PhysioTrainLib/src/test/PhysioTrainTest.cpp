

#ifndef ARDUINO

#include <stdio.h>

#include "Acceleration.h"
#include "Quaternion.h"
#include "EulerAngle.h"
#include "Position.h"
#include "RotationMatrix.h"
#include "Transformation.h"
#include "Filter.h"

#include "Wire.h"
TwoWire         muxWire;

void
print_q(const char *str, Quaternion &q)
{
    printf("%s = %0.4f %0.4f %0.4f %0.4f\n", str, q.getW(), q.getX(), q.getY(), q.getZ());
}


void
print_pos(const char *str, Position &p)
{
    printf("%s = [\n", str);
    printf("  %8.4f\n", p.getX());
    printf("  %8.4f\n", p.getY());
    printf("  %8.4f\n", p.getZ());
    printf("]\n");
}

void
print_rot(const char *str, RotationMatrix &rot)
{
    printf("%s = [\n", str);
    printf("  %8.4f %8.4f %8.4f\n", rot.getElement(0, 0), rot.getElement(0, 1), rot.getElement(0, 2));
    printf("  %8.4f %8.4f %8.4f\n", rot.getElement(1, 0), rot.getElement(1, 1), rot.getElement(1, 2));
    printf("  %8.4f %8.4f %8.4f\n", rot.getElement(2, 0), rot.getElement(2, 1), rot.getElement(2, 2));
    printf("]\n");
}

void
print_trans(const char *str, Transformation &trans)
{
    printf("%s = [\n", str);
    printf("  %8.4f %8.4f %8.4f %8.4f\n", trans.getElement(0, 0), trans.getElement(0, 1), trans.getElement(0, 2), trans.getElement(0, 3));
    printf("  %8.4f %8.4f %8.4f %8.4f\n", trans.getElement(1, 0), trans.getElement(1, 1), trans.getElement(1, 2), trans.getElement(1, 3));
    printf("  %8.4f %8.4f %8.4f %8.4f\n", trans.getElement(2, 0), trans.getElement(2, 1), trans.getElement(2, 2), trans.getElement(2, 3));
    printf("  %8.4f %8.4f %8.4f %8.4f\n", trans.getElement(3, 0), trans.getElement(3, 1), trans.getElement(3, 2), trans.getElement(3, 3));
    printf("]\n");
}

int
main(int argc, char *argv[])
{
    Quaternion q1 = Quaternion(    1.0f,     0.0f,     0.0f,  0.0f);
    Quaternion q2 = Quaternion(    0.0f,  0.7071f,     0.0f,  0.7071f);
    Quaternion q3 = Quaternion( 0.7071f,  0.7071f,     0.0f,  0.0f);
    Quaternion q4 = q2 * q3;
    Quaternion q5 = q2;
    q5.inverse();
    Quaternion q6 = q5 * q2;

    print_q("q4", q4);
    print_q("q5", q5);
    print_q("q6", q6);

    RotationMatrix rot4 = q4.getRotationMatrix();
    RotationMatrix rot5 = q5.getRotationMatrix();

    print_rot("rot4", rot4);
    print_rot("rot5", rot5);

    printf("/*************************************************************************/\n");

    Quaternion q7 = Quaternion( 0.4284f, -0.2863f, -0.0451f,  0.8559f);
    Quaternion q8 = Quaternion( 0.2776f,  0.8976f,  0.3408f, -0.0349f);

    print_q("q5", q5);
    print_q("q6", q6);

    RotationMatrix rot1 = q1.getRotationMatrix();
    RotationMatrix rot7 = q7.getRotationMatrix();
    RotationMatrix rot8 = q8.getRotationMatrix();
    Position       p1(0.0f, 0.0f,  0.0f);
    Position       p2(0.0f, 0.0f, -5.0f);
    Position       p3(0.0f, 0.0f, -3.0f);
    Transformation t1(p1, rot7);
    Transformation t2(p2, rot8);
    Transformation t3(p3, rot1);
    Transformation t4 = t1 * t2 * t3;

    print_trans("t1", t1);
    print_trans("t2", t2);
    print_trans("t3", t3);
    print_trans("t4", t4);
    printf("t4 =[\n%s]\n", t4.toString().c_str());
    
    //t1.print(String("bla"));
    t1.toString();

    printf("/*************************************************************************/\n");

    Quaternion q10 = Quaternion( 0.9239f, -0.3827f,  0.0000f,  0.0000f);
    Quaternion q11 = Quaternion( 0.8660f, -0.5000f,  0.0000f,  0.0000f);

    print_q("q10", q10);
    print_q("q11", q11);

    RotationMatrix rot10 = q10.getRotationMatrix();
    RotationMatrix rot11 = q11.getRotationMatrix();
    Position       p10(0.0f, 0.0f,  0.0f);
    Position       p11(0.0f, 0.0f, -2.8f);
    Position       p12(0.0f, 0.0f, -2.8f);
    Transformation t10(p10, rot10);
    Transformation t11(p10, rot11);
    Transformation t12(p10, rot11);

    Position       p20 = t10 * p11;
    Position       p21 = p20 + (t11 * p12);
    Position       p22 = p21 + (t12 * p10);

    print_trans("t10", t10);
    print_trans("t11", t11);
    print_trans("t12", t12);

    print_pos("p20", p20);
    print_pos("p21", p21);
    print_pos("p22", p22);

    return 0;
}

#endif

