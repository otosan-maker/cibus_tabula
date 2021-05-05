#ifndef PRODUCTOCPP
#define PRODUCTOCPP
#include <Arduino.h>

#define MAX_FECHA  10
#define MAX_NOMBRE 15
#define MAX_LOCATION 16
#define MAX_NUM_PRODUCTOS 200
class producto
{
private:
    /* data */
public:
    int     m_idproducto;
    char    m_f_alta[MAX_FECHA+1];
    char    m_f_baja[MAX_FECHA+1];
    char    m_nombreProducto[MAX_NOMBRE+1];
    char    m_localizacion[MAX_LOCATION+1];
    boolean m_seleccionado;

    producto(int id,const char * f_alta,const char * f_baja,const char * prod,const char * loc);
    producto();
    ~producto();

    void set(int id,const char * f_alta,const char * f_baja,const char * prod,const char * loc);
};





#endif