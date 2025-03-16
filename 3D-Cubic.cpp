#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GLUT/GLUT.h>
//using namespace std;
const GLdouble pi = 3.14159;

typedef GLfloat Matrix4x4 [4][4];
Matrix4x4 matComposite;
bool mouseDown = false;

float xrot = 0.0f;
float yrot = 0.0f;

float xdiff = 0.0f;
float ydiff = 0.0f;
/*
void Cubic(wcPt3D verts);

class wcPt3D
{
  public:
     GLfloat x, y, z;
};

void Calc3DPoint(void)
{
    x  = (-1)*x;
    xa = cr1*x - sr1*z;
    za = sr1*x + cr1*z;
    
    x  = cr2*xa + sr2*y;
    ya = cr2*y  - sr2*xa;
    
    z  = cr3*za - sr3*ya;
    y  = sr3*za + cr3*ya;
    
    x=x+mx; y=y+my; z=z+mz;
    
    sx = d*x/z;
    sy = d*y/z;
    return;
}
// 使用给定的参数逐个元素地构建透视投影矩阵并返回该矩阵。
get_projection_matrix(float eye_fov, float aspect_ratio,
    float zNear, float zFar)
{
    Eigen::Matrix4f projection = Eigen::Matrix4f::Identity();

    //M persp->ortho,透视投影转换为正交投影
     persp2ortho = Eigen::Matrix4f::Identity();
    persp2ortho << zNear, 0, 0, 0,
        0, zNear, 0, 0,
        0, 0, zNear + zFar, -(zNear * zFar),
        0, 0, 1, 0;

    //M ortho
    Eigen::Matrix4f ortho = Eigen::Matrix4f::Identity();
    Eigen::Matrix4f scale = Eigen::Matrix4f::Identity();
    Eigen::Matrix4f transformation = Eigen::Matrix4f::Identity();
    // t means top, b means bottom,l means left,r means right.
    float t = tanf(eye_fov / 2) * abs(zNear);
    float b = -t;
    float r = aspect_ratio * t;
    float l = -r;

    // scale矩阵，将原图形缩放为标准长度为2的立方体
    scale << 2 / (r - l), 0, 0, 0,
        0, 2 / (t - b), 0, 0,
        0, 0, 2 / (zNear - zFar), 0,
        0, 0, 0, 1;
    // 将立方体的中心移至源点
    transformation << 1, 0, 0, -((r + l) / 2),
        0, 1, 0, -((t + b) / 2),
        0, 0, 1, -((zNear + zFar) / 2),
        0, 0, 0, 1;
    ortho = scale * transformation;
    projection = ortho * persp2ortho;
    return projection;
}

void setPixel(GLint x, GLint y,GLint z)//在屏幕上画一个点
{
    glPointSize(3.0f);
    glColor3f(1, 0, 0);//设置画点的颜色
    glBegin(GL_POINTS);
    glVertex3i(x, y,z);
    glEnd();
}

void BresenhamLine(int x0, int y0, int z0,int x1, int y1,int z1,int plane)
{
    //glClear(GL_COLOR_BUFFER_BIT);
 //清除窗口显示内容

    int xx, yy,zz,dxx, dyy,xx11,yy11,e,txx,tyy;
    switch (plane)
    {
        case 1://平面xy中
        {
            xx = x0;
            yy = y0;
            zz = z0;//z坐标不变
            xx11=x1;
            yy11=y1;
            dxx = x1 - x0;
            dyy = y1 - y0;
            //确定步长tx，ty，斜率为正或为负，且只考虑左/右上or左/右下，左/右边的情况不加步长即可
            txx =((x1>x0)?1:(dxx = -dxx, -1));
            tyy =((y1>y0)?1:(dyy = -dyy, -1));//!!!!!!!
        }
            break;
        case 2://平面xz中
        {
            xx = x0;
            yy = z0;
            zz = y0;//y坐标不变
            xx11=x1;
            yy11=z1;
            dxx = x1 - x0;
            dyy = z1 - z0;
            //确定步长tx，ty，斜率为正或为负，且只考虑左/右上or左/右下，左/右边的情况不加步长即可
            txx =((x1>x0)?1:(dxx = -dxx, -1));
            tyy =((z1>z0)?1:(dyy = -dyy, -1));
        }
            break;
        case 3://平面yz中
        {
            xx = y0;
            yy = z0;
            zz = x0;//y坐标不变
            xx11=y1;
            yy11=z1;
            dxx = y1 - y0;
            dyy = z1 - z0;
            //确定步长tx，ty，斜率为正或为负，且只考虑左/右上or左/右下，左/右边的情况不加步长即可
            txx =((y1>y0)?1:(dxx = -dxx, -1));
            tyy =((z1>z0)?1:(dyy = -dyy, -1));//!!!!!!!
        }
            break;
 
    }

    int flag = 0;  //斜率绝对值标志，0表示斜率绝对值小于1
    if (abs(dyy) > abs(dxx))//斜率绝对值大于1
    {
        flag = 1;
    }

    //glBegin(GL_POINTS);
    //glVertex3i(xx, yy,zz);
    if (flag == 0) {
        e = -dxx;
        while (xx != xx11)
        {
            xx += txx;
            e += 2 * dyy;
            if (e >= 0)
            {
                yy += tyy;
                e -= 2 * dxx;
            }
            //glVertex3i(xx, yy,zz);
            setPixel(xx, yy,zz);
        }
    }
    else {
        e = -dyy;
        while (yy != yy11)
        {
            yy += tyy;
            e += 2 * dxx;
            if (e >= 0)
            {
                xx += txx;
                e -= 2 * dyy;
            }
            glVertex3i(xx, yy,zz);
            setPixel(xx, yy,zz);
        }
    }
    //glEnd();
    //glFlush();
}

void DrawLine()//画线回调函数
{
    //glClear(GL_COLOR_BUFFER_BIT);//清除窗口显示内容
    glBegin(GL_POINTS);
    glColor3f(1, 0, 0);//设置画点的颜色

    BresenhamLine(20, 20, 20,-20,20,20,1);//xy面画线
    BresenhamLine(20, 20, 20,20,-20,20,1);
    BresenhamLine(-20, -20, -20,-20,+20,-20,1);
    BresenhamLine(-20, -20, -20,20,-20,-20,1);
    BresenhamLine(20, 20, -20,20,-20,-20,1);
    BresenhamLine(20, 20, -20,-20,+20,-20,1);
    BresenhamLine(-20, -20, 20,-20,20,20,1);
    BresenhamLine(-20, -20, 20,20,-20,20,1);
    
    BresenhamLine(20, 20, 20,20,20,-20,2);//xz面画线
    BresenhamLine(-20, 20, 20,-20,20,-20,2);
    BresenhamLine(-20, -20, 20,-20,-20,-20,2);
    BresenhamLine(20, -20, 20,20,-20,-20,2);
    glEnd();
    glFlush();
}


//矩阵变换函数定义部分

 void matrix4x4SetIdentity (Matrix4x4 matIdent4x4)//构建单位矩阵
{
   GLint row, col;

   for (row = 0; row < 4; row++)
      for (col = 0; col < 4; col++)
         matIdent4x4 [row][col] = (row == col);
}

void matrix4x4PreMultiply (Matrix4x4 m1, Matrix4x4 m2)//矩阵计算
{
   GLint row, col;
   Matrix4x4 matTemp;

   for (row = 0; row < 4; row++)
      for (col = 0; col < 4 ; col++)
         matTemp [row][col] = m1 [row][0] * m2 [0][col] + m1 [row][1] * m2 [1][col] + m1 [row][2] * m2 [2][col]+m1 [row][3] * m2 [3][col];

   for (row = 0; row < 4; row++)
      for (col = 0; col < 4; col++)
         m2 [row][col] = matTemp [row][col];
}

void translate3D (GLfloat tx, GLfloat ty, GLfloat tz)//平移矩阵
{
   Matrix4x4 matTransl;

   //转换矩阵初始化为单位矩阵
   matrix4x4SetIdentity (matTransl);

   matTransl [0][3] = tx;
   matTransl [1][3] = ty;
   matTransl [2][3] = tz;

   //将 matTransl 与复合矩阵连接起来。
   matrix4x4PreMultiply (matTransl, matComposite);
}

void rotate3D (wcPt3D pivotPt, GLfloat theta)//旋转矩阵*****
{
   Matrix4x4 matRot;

    //将旋转矩阵初始化为单位矩阵。
   matrix4x4SetIdentity (matRot);

   matRot [0][0] = cos (theta);
   matRot [0][1] = -sin (theta);
   matRot [0][2] = pivotPt.x * (1 - cos (theta)) +
                        pivotPt.y * sin (theta);
   matRot [1][0] = sin (theta);
   matRot [1][1] = cos (theta);
   matRot [1][2] = pivotPt.y * (1 - cos (theta)) -
                        pivotPt.x * sin (theta);

   //将 matRot 与复合矩阵连接起来。
   matrix4x4PreMultiply (matRot, matComposite);
}

void scale3D (GLfloat sx, GLfloat sy, wcPt3D fixedPt)//缩放矩阵*****
{
   Matrix4x4 matScale;

   matrix4x4SetIdentity (matScale);

   matScale [0][0] = sx;
   matScale [0][2] = (1 - sx) * fixedPt.x;
   matScale [1][1] = sy;
   matScale [1][2] = (1 - sy) * fixedPt.y;

   matrix4x4PreMultiply (matScale, matComposite);
}

void transformVerts3D (GLint nVerts, wcPt3D * verts)//使用复合矩阵，计算转换后的坐标。******
{
   GLint k;
   GLfloat temp;

   for (k = 0; k < nVerts; k++)
   {
      temp = matComposite [0][0] * verts [k].x + matComposite [0][1] *
             verts [k].y + matComposite [0][2];
      verts [k].y = matComposite [1][0] * verts [k].x + matComposite [1][1] *
                  verts [k].y + matComposite [1][2];
         verts [k].x = temp;
   }
}

 */
 // 绘制正方体
 void drawBox()
 {
     glBegin(GL_LINES);
 // FRONT
     glColor3f(1.0f, 0.0f, 0.0f);
     glVertex3f(0.5f, 0.5f, -0.5f);
     glVertex3f(0.5f, -0.5f, -0.5f);
     
     glVertex3f(0.5f, 0.5f, 0.5f);
     glVertex3f(0.5f, -0.5f, 0.5f);
     
     glVertex3f(0.5f, 0.5f, 0.5f);
     glVertex3f(0.5f, 0.5f, -0.5f);
     
     glVertex3f(0.5f, -0.5f, 0.5f);
     glVertex3f(0.5f, -0.5f, -0.5f);
 // BACK
     glColor3f(0.0f, 0.0f, 1.0f);

     glVertex3f(-0.5f, -0.5f, 0.5f);
     glVertex3f(-0.5f, 0.5f, 0.5f);
     
     glVertex3f(-0.5f, -0.5f, -0.5f);
     glVertex3f(-0.5f, +0.5f, -0.5f);
     
     glVertex3f(-0.5f, 0.5f, 0.5f);
     glVertex3f(-0.5f, 0.5f, -0.5f);
     
     glVertex3f(-0.5f, -0.5f, 0.5f);
     glVertex3f(-0.5f, -0.5f, -0.5f);
 //BESIDES
     glColor3f(0.0f, 1.0f, 0.0f);

     glVertex3f(-0.5f, -0.5f,-0.5f);
     glVertex3f(0.5f, -0.5f, -0.5f);

     glVertex3f(0.5f, 0.5f, -0.5f);
     glVertex3f(-0.5f, 0.5f, -0.5f);
     
     glVertex3f(0.5f, 0.5f, 0.5f);
     glVertex3f(-0.5f, 0.5f, 0.5f);
     
     glVertex3f(-0.5f, -0.5f, 0.5f);
     glVertex3f(0.5f, -0.5f, 0.5f);
     
     glColor3f(0.0,0.0,0.0);
     glVertex3f(0,0,-300);
     glVertex3f(0,0,300);
     glVertex3f(0,-300,0);
     glVertex3f(0,300,0);
     glVertex3f(-300,0,0);
     glVertex3f(300,0,0);
     glEnd();
 }

// 绘制函数
void display1() {//斜二测投影
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(3.0f, 1.0f, 1.0f,  0.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f);
    glOrtho(1, -2, 1, -1, 1, -1);
    glPushMatrix();
    
    // 实现鼠标旋转的核心
    glRotatef(xrot, 1.0f, 0.0f, 0.0f);
    glRotatef(yrot, 0.0f, 1.0f, 0.0f);
    
    drawBox();
    //DrawLine();
    
    glFlush();
    glutSwapBuffers();
}

void display2() {//正投影
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(3.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f);
    glOrtho(1, -1, 1, -1, 1, -1);
    glPushMatrix();
    
    // 实现鼠标旋转的核心
    glRotatef(xrot, 1.0f, 0.0f, 0.0f);
    glRotatef(yrot, 0.0f, 1.0f, 0.0f);
    
    drawBox();
    //DrawLine();
    
    glFlush();
    glutSwapBuffers();
}

void display3() {//斜等轴投影
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(3.0f, 3.0f, 3.0f,  0.0f, 0.0f, 0.0f,   0.0f, 1.0f, 1.0f);
    //glOrtho(1, -1, 1, -1, 1, -1);
    glPushMatrix();
    
    // 实现鼠标旋转的核心
    glRotatef(xrot, 1.0f, 0.0f, 0.0f);
    glRotatef(yrot, 0.0f, 1.0f, 0.0f);
    
    drawBox();
    //DrawLine();
    
    glFlush();
    glutSwapBuffers();
}

void resize(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, w, h);

    gluPerspective(45.0f, 1.0f * w / h, 1.0f, 100.0f);
    //display1();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// 鼠标事件
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mouseDown = true;
        xdiff = x - yrot;
        ydiff = -y + xrot;
        std::cout << "xdiff:" << xdiff << "\tydiff" << ydiff << std::endl;
    }
    else
        mouseDown = false;
}

// 鼠标移动事件
void mouseMotion(int x, int y) {
    if (mouseDown) {
        yrot = x - xdiff;
        xrot = y + ydiff;
        std::cout << "yrot:" << yrot << "\txrot" << xrot << std::endl;

        glutPostRedisplay();
    }
}
GLenum fillMode = GL_SMOOTH;  // Initial polygon fill: color interpolation.

void fillOption (GLint selectedOption)
{
   switch (selectedOption) {
      case 1:  display1();       break;
      case 2:  display2();      break;
       case 3: display3();    break;
   }
   glutPostRedisplay ( );
}
//键盘事件
/*
void trans (GLint reductionKey, GLint xMouse, GLint yMouse)
{
   switch (reductionKey)
   {
      case GLUT_KEY_LEFT:
         transLeft();
         break;
      case GLUT_KEY_RIGHT:
           transRight();
         break;
       case GLUT_KEY_UP:
           transUp();
          break;
       case GLUT_KEY_DOWN:
           transDown();
          break;
      default:
         break;
   }
}
*/
int main(int argc, char* argv[]) {
    glutInit(&argc, argv);

    glutInitWindowPosition(50, 50);
    glutInitWindowSize(500, 500);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutCreateWindow("3D-Cubic");

    glutDisplayFunc(display1);


    glClearColor(0.93f, 0.93f, 0.93f, 0.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glClearDepth(1.0f);
    
    glutCreateMenu (fillOption);              // Create pop-up menu.
     glutAddMenuEntry ("斜二测投影", 1);
     glutAddMenuEntry ("正投影", 2);
     glutAddMenuEntry ("斜等轴投影", 3);

    /*  Select a menu option using the right mouse button.  */
    glutAttachMenu (GLUT_RIGHT_BUTTON);
    
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    //glutSpecialFunc (trans);

    glutReshapeFunc(resize);

    glutMainLoop();
    return 0;
}
