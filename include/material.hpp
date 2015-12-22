#ifndef _MATERIAL
#define _MATERIAL

struct Material{
    void material_difuso(){
        GLfloat light_diffuse[]={1.0, 1.0, 1.0, 1.0};
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light_diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, light_diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, light_diffuse);
        	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20);
    }
    void material_no_difuso(){
        GLfloat light_diffuse[]={0.0, 0.0, 0.0, 0.0};
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light_diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, light_diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, light_diffuse);
        	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20);
    }
    void material_amarillo(){
        GLfloat light_diffuse[]={0.0, 1.0, 1.0, 0.0};
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light_diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, light_diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, light_diffuse);
        	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20);
    }
    void material_azul(){
        GLfloat light_diffuse[]={0.0, 1.0, 0.0, 0.0};
        GLfloat light_diffuse1[]={1.0, 1.0, 0.0, 0.0};
        GLfloat light_diffuse2[]={0.0, 1.0, 1.0, 0.0};
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light_diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, light_diffuse1);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, light_diffuse2);
        	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20);
    }
    void material_m(){
        GLfloat light_diffuse[]={0.0, 0.5, 0.5, 0.0};
        GLfloat light_diffuse1[]={0.5, 0.5, 0.0, 0.0};
        GLfloat light_diffuse2[]={0.0, 0.5, 0.5, 0.0};
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light_diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, light_diffuse1);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, light_diffuse2);
        	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10);
        
    }
    void material_m1(){
        GLfloat light_diffuse[]={0.0, 0.0, 0.0, 0.0};
        GLfloat light_diffuse1[]={0.1, 0.1, 0.0, 0.0};
        GLfloat light_diffuse2[]={0.0, 0.1, 0.1, 0.0};
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light_diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, light_diffuse1);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, light_diffuse2);
        	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10);
    }
};


#endif