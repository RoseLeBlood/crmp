#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <QtOpenGL/QGLWidget>
#include "glwidget.h"



GLWidget::GLWidget() : QGLWidget()
{
    //setFixedSize(WIDGET_W,WIDGET_H)
    //setFixedWidth(WIDGET_W);
    setFormat(QGLFormat(QGL::DoubleBuffer));

    spectrumsize = this->width();
    spectrum[0] = new float[spectrumsize];
    spectrum[1] = new float[spectrumsize];

    memset(spectrum[0], 0, spectrumsize);
    memset(spectrum[1], 0, spectrumsize);

}
GLWidget::~GLWidget()
{


    delete spectrum[0];
}
void GLWidget::setup_opengl ( int w, int h)
{
    glShadeModel ( GL_SMOOTH );
    /* Culling. */
       glCullFace( GL_BACK );
       glFrontFace( GL_CCW );
        glEnable( GL_CULL_FACE );
    /* Set the clear color.*/
    glViewport(0,0,w,h);

    glMatrixMode ( GL_TEXTURE );
    glLoadIdentity();


    glMatrixMode (GL_PROJECTION);
         glLoadIdentity ();
         glOrtho (0, w, h, 0, 0, 1);

         glMatrixMode (GL_MODELVIEW);
         glLoadIdentity();

    glDrawBuffer ( GL_BACK );
    glReadBuffer ( GL_BACK );
    glEnable ( GL_BLEND );

    glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    glEnable ( GL_LINE_SMOOTH );
    glEnable ( GL_POINT_SMOOTH );
    glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );

    glLineStipple ( 2, 0xAAAA );

    spectrumsize = this->width();
    spectrum[0] = new float[spectrumsize];
    spectrum[1] = new float[spectrumsize];
}

void GLWidget::initializeGL()
{

    setup_opengl(this->width(), this->height());

}
void GLWidget::setVisible(bool visual)
{
    QGLWidget::setVisible(visual);

    if(!visual)
    {
        this->killTimer(m_timer);
    }
    else
    {
       m_timer = this->startTimer(11);
    }
}

void GLWidget::DrawLine(Vector2 start, Vector2 end)
{
    glBegin(GL_LINE_STRIP);
    glVertex2f(start.x, start.y);
    glVertex2f(end.x, end.y);
    glEnd();
}
void GLWidget::timerEvent(QTimerEvent *)
{
  this->updateGL();
}


void GLWidget::paintGL()
{
    if(this->isVisible() == false)
    {
        swapBuffers();
        return;

    }
    if( !raStream::Instance().IsPlaying())
    {
        memset(spectrum[0], 0, spectrumsize);
        memset(spectrum[1], 0, spectrumsize);

    }
    else
    {
        raStream::Instance().GetChannel()->getWaveData(spectrum[0], spectrumsize, 0);
        raStream::Instance().GetChannel()->getWaveData(spectrum[1], spectrumsize, 1);
    }

    //draw scene here
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);



    {
        float y1, y2;
        float ynext1, ynext2;


        for (int x = 0; x < spectrumsize-1; x++)
        {
            // Brechnung des 1. Punktes (y Koordinate) startpunkt der Linie
            y1 = ((spectrum[0][x] + 1) / 2.0f) * this->height();
            // Berechnung des 2. Punktes (y Koordinate) endpunkt der Linie
            ynext1 = ((spectrum[0][x+1] + 1) / 2.0f) * this->height();


            // Brechnung des 1. Punktes (y Koordinate) startpunkt der Linie
            y2 = (spectrum[1][x] + 1) / 2.0f * this->height();
            // Berechnung des 2 Punktes (y Koordinate) endpunkt der Linie
            ynext2 = (spectrum[1][x+1] + 1) / 2.0f * this->height();

            glColor3f(1.0f,0.0f,0.0f);
            DrawLine(Vector2((x+1), (y1)+25), Vector2((x+2), (ynext1)+25));
            glColor3f(0.0f,1.0f,0.0f);
            DrawLine(Vector2(x+1, y2), Vector2(x+2, ynext2));
        }
     }


}









