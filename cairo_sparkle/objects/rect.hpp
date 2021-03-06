


class casp_rect : public casp_object{

public:
     casp_rect * target = NULL;
     
     // stroke
     bool stroke = false;
     double stroke_w = 0, d_stroke_w;
     casp_rgb color_stroke = casp_rgb_null;

     casp_rect(double _x=0, double _y=0, double _w=0, double _h=0,
                    casp_rgb _color=casp_rgb_null,
                    double _pivx=0.5, double _pivy=0.5){
          setup_rect(_x, _y, _w, _h, _color, _pivx, _pivy);
     }


     void setup_rect(double _x=0, double _y=0, double _w=0, double _h=0,
                    casp_rgb _color=casp_rgb_null,
                    double _pivx=0.5, double _pivy=0.5){
          xywh.x=_x;
          xywh.y=_y;
          xywh.w=_w;
          xywh.h=_h;
          color =_color;

          pivot.x=_pivx;
          pivot.y=_pivy;
          setup_surface();
     }


     void setup_stroke(bool _stroke, double _stroke_w, casp_rgb _color_stroke=casp_rgb_null){
          stroke      =_stroke;
          stroke_w    =_stroke_w;
          color_stroke=_color_stroke;
     }


     void draw_rect(bool strokein = false){
          casp_rgb d_color = strokein ? color_stroke:color;
          cairo_set_source_rgba(surface->cr, d_color.r, d_color.g, d_color.b, d_color.a);

          if(make_allowed()) d_xywh = surface->make_xywh(xywh);
          
          cairo_rectangle(surface->cr, d_xywh.x-d_xywh.w*pivot.x, d_xywh.y-d_xywh.h*pivot.y,
                              d_xywh.w, d_xywh.h);
          if(strokein){
               if(make_allowed()) d_stroke_w = surface->make_w(stroke_w);
               cairo_set_line_width(surface->cr, d_stroke_w);
               cairo_stroke(surface->cr);
          }
          else{
               cairo_fill(surface->cr);
               if(stroke) draw_rect(true);
          }

          d_set = true;
          
     }


};
