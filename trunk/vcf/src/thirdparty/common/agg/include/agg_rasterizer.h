//----------------------------------------------------------------------------
// Anti-Grain Geometry - Version 2.0 
// Copyright (C) 2002 Maxim Shemanarev (McSeem)
//
// Permission to copy, use, modify, sell and distribute this software 
// is granted provided this copyright notice appears in all copies. 
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//
// The author gratefully acknowleges the support of David Turner, 
// Robert Wilhelm, and Werner Lemberg - the authors of the FreeType 
// libray - in producing this work. See http://www.freetype.org for details.
//
//----------------------------------------------------------------------------
// Contact: mcseem@antigrain.com
//          mcseemagg@yahoo.com
//          http://www.antigrain.com
//----------------------------------------------------------------------------
//
// Class rasterizer
//         
//
//----------------------------------------------------------------------------
#ifndef AGG_RASTERIZER_INCLUDED
#define AGG_RASTERIZER_INCLUDED

#include <string.h>
#include <math.h>
#include "thirdparty/common/agg/include/agg_basics.h"
#include "thirdparty/common/agg/include/agg_math.h"

namespace agg
{

    //------------------------------------------------------------------------
    // These constants determine the subpixel accuracy, to be more precise, 
    // the number of bits of the fractional part of the coordinates. 
    // The possible coordinate capacity in bits can be calculated by formula:
    // sizeof(int) * 8 - poly_base_shift * 2, i.e, for 32-bit integers and
    // 8-bits fractional part the capacity is 16 bits or [-32768...32767].
    enum
    {
        poly_base_shift = 8,
        poly_base_size  = 1 << poly_base_shift,
        poly_base_mask  = poly_base_size - 1
    };
    
    //------------------------------------------------------------------------
    inline int poly_coord(double c)
    {
        return int(c * poly_base_size);
    }

    //------------------------------------------------------------------------
    // A pixel cell. There're no constructors defined and it was done 
    // intentionally in order to avoid extra overhead when allocating an 
    // array of cells.
    struct cell
    {
        int16 x;
        int16 y;
        int   packed_coord;
        int   cover;
        int   area;

        void set(int x, int y, int c, int a);
        void set_coord(int x, int y);
        void set_cover(int c, int a);
        void add_cover(int c, int a);
    };


    //------------------------------------------------------------------------
    // An internal class that implements the main rasterization algorithm.
    // Used in the rasterizer. Should not be used direcly.
    class outline
    {
        enum
        {
            cell_block_shift = 12,
            cell_block_size  = 1 << cell_block_shift,
            cell_block_mask  = cell_block_size - 1,
            cell_block_pool  = 256,
            cell_block_limit = 1024
        };

    public:

        ~outline();
        outline();

        void reset();

        void move_to(int x, int y);
        void line_to(int x, int y);

        int min_x() const { return m_min_x; }
        int min_y() const { return m_min_y; }
        int max_x() const { return m_max_x; }
        int max_y() const { return m_max_y; }

        unsigned num_cells() const {return m_num_cells; }
        const cell* const* cells();

    private:
        outline(const outline&);
        const outline& operator = (const outline&);

        void set_cur_cell(int x, int y);
        void add_cur_cell();
        void sort_cells();
        void render_scanline(int ey, int x1, int y1, int x2, int y2);
        void render_line(int x1, int y1, int x2, int y2);
        void allocate_block();
        
        static void qsort_cells(cell** start, unsigned num);

    private:
        unsigned  m_num_blocks;
        unsigned  m_max_blocks;
        unsigned  m_cur_block;
        unsigned  m_num_cells;
        cell**    m_cells;
        cell*     m_cur_cell_ptr;
        cell**    m_sorted_cells;
        unsigned  m_sorted_size;
        cell      m_cur_cell;
        int       m_cur_x;
        int       m_cur_y;
        int       m_close_x;
        int       m_close_y;
        int       m_min_x;
        int       m_min_y;
        int       m_max_x;
        int       m_max_y;
        unsigned  m_flags;
    };


    //----------------------------------------------------------------------------
    enum filling_rule_e
    {
        fill_non_zero,
        fill_even_odd
    };
    
    //----------------------------------------------------------------------------
    struct null_gamma
    {
        static int calculate(int val) { return val; }
    };
    

    //----------------------------------------------------------------------------
    class gamma8
    {
    public:
        gamma8() 
        { 
            memcpy(m_gamma, s_default_gamma, sizeof(m_gamma)); 
        }

        void copy_from(const unsigned char* gamma)
        {
            memcpy(m_gamma, gamma, sizeof(m_gamma));
        }

        void gamma(double g)
        {
            unsigned i;
            for(i = 0; i < 256; i++)
            {
                m_gamma[i] = (unsigned char)(pow(double(i) / 255.0, g) * 255.0);
            }
        }

        int calculate(int val) const { return m_gamma[val]; }

    private:
        unsigned char m_gamma[256];
        static unsigned char s_default_gamma[];
    };

    
    void extend_triangle(double x1, double y1,
                         double x2, double y2,
                         double x3, double y3,
                         double* x, double* y,
                         double d);


    //========================================================================
    // Polygon rasterizer that is used to render filled polygons with 
    // high-quality Anti-Aliasing. Internally, by default, the class uses 
    // integer coordinates in format 24.8, i.e. 24 bits for integer part 
    // and 8 bits for fractional - see poly_base_shift. This class can be 
    // used in the following  way:
    //
    // 1. filling_rule(filling_rule_e ft) - optional.
    //
    // 2. gamma() - optional.
    //
    // 3. reset()
    //
    // 4. move_to(x, y) / line_to(x, y) - make the polygon. One can create 
    //    more than one contour, but each contour must consist of at least 3
    //    vertices, i.e. move_to(x1, y1); line_to(x2, y2); line_to(x3, y3);
    //    is the absolute minimum of vertices that define a triangle.
    //    The algorithm does not check either the number of vertices nor
    //    coincidence of their coordinates, but in the worst case it just 
    //    won't draw anything.
    //    The orger of the vertices (clockwise or counterclockwise) 
    //    is important when using the non-zero filling rule (fill_non_zero).
    //    In this case the vertex order of all the contours must be the same
    //    if you want your intersecting polygons to be without "holes".
    //    You actually can use different vertices order. If the contours do not 
    //    intersect each other the order is not important anyway. If they do, 
    //    contours with the same vertex order will be rendered without "holes" 
    //    while the intersecting contours with different orders will have "holes".
    //
    // filling_rule() and gamma() can be called anytime before "sweeping".
    //------------------------------------------------------------------------
    template<class Scanline, class GammaFunction=null_gamma> 
    class rasterizer
    {
    public:
        enum
        {
            aa_shift = Scanline::aa_shift,
            aa_num   = 1 << aa_shift,
            aa_mask  = aa_num - 1,
            aa_2num  = aa_num * 2,
            aa_2mask = aa_2num - 1
        };
        typedef typename Scanline::alpha_mask_type alpha_mask_type;
        rasterizer() : m_filling_rule(fill_non_zero) {}
        rasterizer(alpha_mask_type& am) :
            m_scanline(am),
            m_filling_rule(fill_non_zero)
        {
        }


        //------------------------------------------------------------------------
        void reset() { m_outline.reset(); }

        //------------------------------------------------------------------------
        void filling_rule(filling_rule_e filling_rule) 
        { 
            m_filling_rule = filling_rule; 
        }

        //------------------------------------------------------------------------
        GammaFunction& gamma()    { return m_gamma;    }
        Scanline&      scanline() { return m_scanline; }

        //------------------------------------------------------------------------
        void move_to(int x, int y) { m_outline.move_to(x, y); }
        void line_to(int x, int y) { m_outline.line_to(x, y); }

        //------------------------------------------------------------------------
        void move_to_d(double x, double y) { m_outline.move_to(poly_coord(x), 
                                                               poly_coord(y)); }
        void line_to_d(double x, double y) { m_outline.line_to(poly_coord(x), 
                                                               poly_coord(y)); }

        //------------------------------------------------------------------------
        int min_x() const { return m_outline.min_x(); }
        int min_y() const { return m_outline.min_y(); }
        int max_x() const { return m_outline.max_x(); }
        int max_y() const { return m_outline.max_y(); }

        //------------------------------------------------------------------------
        rect bounding_box() const
        {
            return rect(m_outline.min_x(), m_outline.min_y(),
                        m_outline.max_x(), m_outline.max_y());
        }

        //------------------------------------------------------------------------
        unsigned calculate_alpha(int area) const
        {
            int cover = area >> (poly_base_shift*2 + 1 - aa_shift);

            if(cover < 0) cover = -cover;
            if(m_filling_rule == fill_even_odd)
            {
                cover &= aa_2mask;
                if(cover > aa_num)
                {
                    cover = aa_2num - cover;
                }
            }
            if(cover > aa_mask) cover = aa_mask;
            return cover;
        }


        //------------------------------------------------------------------------
        template<class Renderer> void render(Renderer& r, int dx=0, int dy=0)
        {
            if(m_outline.num_cells() == 0) return;
            const cell* const* cells = m_outline.cells();
            if(cells == 0) return;

            int x, y;
            int cover;
            int alpha;
            int area;

            m_scanline.reset(m_outline.min_x(), m_outline.max_x(), dx, dy);
            r.prepare();

            cover = 0;
            const cell* cur_cell = *cells++;
            for(;;)
            {
                const cell* start_cell = cur_cell;

                int coord  = cur_cell->packed_coord;
                x = cur_cell->x;
                y = cur_cell->y;

                area   = start_cell->area;
                cover += start_cell->cover;

                //accumulate all start cells
                while((cur_cell = *cells++) != 0)
                {
                    if(cur_cell->packed_coord != coord) break;
                    area  += cur_cell->area;
                    cover += cur_cell->cover;
                }

                if(area)
                {
                    alpha = calculate_alpha((cover << (poly_base_shift + 1)) - area);
                    if(alpha)
                    {
                        if(m_scanline.is_ready(y))
                        {
                            m_scanline.alpha_mask();
                            r.render(m_scanline);
                            m_scanline.reset_spans();
                        }
                        m_scanline.add_cell(x, y, m_gamma.calculate(alpha));
                    }
                    x++;
                }

                if(!cur_cell) break;

                if(cur_cell->x > x)
                {
                    alpha = calculate_alpha(cover << (poly_base_shift + 1));
                    if(alpha)
                    {
                        if(m_scanline.is_ready(y))
                        {
                            m_scanline.alpha_mask();
                            r.render(m_scanline);
                            m_scanline.reset_spans();
                        }
                        m_scanline.add_span(x, y, 
                                            cur_cell->x - x, 
                                            m_gamma.calculate(alpha));
                    }
                }
            } 
        
            if(m_scanline.num_spans())
            {
                m_scanline.alpha_mask();
                r.render(m_scanline);
            }
        }


        //------------------------------------------------------------------------
        bool hit_test(int tx, int ty);


        //------------------------------------------------------------------------
        template<class Renderer, class Attr>
        void render_gouraud(Renderer& r, Attr attr, double d=0.0)
        {
            if(d == 0.0)
            {
                move_to_d(attr.m_coord[0].x, attr.m_coord[0].y);
                line_to_d(attr.m_coord[1].x, attr.m_coord[1].y);
                line_to_d(attr.m_coord[2].x, attr.m_coord[2].y);
            }
            else
            {
                double x[6];
                double y[6];
                extend_triangle(attr.m_coord[0].x, attr.m_coord[0].y,
                                attr.m_coord[1].x, attr.m_coord[1].y,
                                attr.m_coord[2].x, attr.m_coord[2].y,
                                x, y, d);

                calc_intersection(x[4], y[4], x[5], y[5],
                                  x[0], y[0], x[1], y[1],
                                  &attr.m_coord[0].x, &attr.m_coord[0].y);

                calc_intersection(x[0], y[0], x[1], y[1],
                                  x[2], y[2], x[3], y[3],
                                  &attr.m_coord[1].x, &attr.m_coord[1].y);

                calc_intersection(x[2], y[2], x[3], y[3],
                                  x[4], y[4], x[5], y[5],
                                  &attr.m_coord[2].x, &attr.m_coord[2].y);

                move_to_d(x[0], y[0]);
                line_to_d(x[1], y[1]);
                line_to_d(x[2], y[2]);
                line_to_d(x[3], y[3]);
                line_to_d(x[4], y[4]);
                line_to_d(x[5], y[5]);
            }
            r.attribute(attr);
            render(r);
        }


        //------------------------------------------------------------------------
        template<class VertexSource>
        void add_path(VertexSource& vs, unsigned id=0)
        {
            double x;
            double y;

            unsigned cmd;
            vs.rewind(id);
            while(!is_stop(cmd = vs.vertex(&x, &y)))
            {
                if(is_move_to(cmd)) 
                {
                    m_outline.move_to(poly_coord(x), poly_coord(y));
                }
                else 
                {
                    m_outline.line_to(poly_coord(x), poly_coord(y));
                }
            }
        }


        //------------------------------------------------------------------------
        template<class VertexSource>
        void add_path(VertexSource& vs, double dx, double dy, unsigned id=0)
        {
            double x;
            double y;

            unsigned cmd;
            vs.rewind(id);
            while(!is_stop(cmd = vs.vertex(&x, &y)))
            {
                x += dx;
                y += dy;
                if(is_move_to(cmd)) 
                {
                    m_outline.move_to(poly_coord(x), poly_coord(y));
                }
                else 
                {
                    m_outline.line_to(poly_coord(x), poly_coord(y));
                }
            }
        }


        //------------------------------------------------------------------------
        template<class VertexIterator>
        void add_path(VertexIterator begin, VertexIterator end, 
                      double dx=0, double dy=0)
        {
            while(begin != end)
            {
                double x = begin->x + dx;
                double y = begin->y + dy;

                if(is_move_to(begin->cmd)) 
                {
                    m_outline.move_to(poly_coord(x), poly_coord(y));
                }
                else 
                {
                    m_outline.line_to(poly_coord(x), poly_coord(y));
                }
                ++begin;
            }
        }


        //------------------------------------------------------------------------
        template<class Renderer, class VertexSource, class AttrStorage, class PathId>
        void render_all_paths(Renderer& r, 
                              VertexSource& vs, 
                              const AttrStorage& as, 
                              const PathId& id,
                              unsigned num_paths)
        {
            for(unsigned i = 0; i < num_paths; i++)
            {
                reset();
                add_path(vs, id[i]);
                r.attribute(as[i]);
                render(r);
            }
        }


        //------------------------------------------------------------------------
        template<class Renderer, class VertexSource, class AttrStorage, class PathId>
        void render_all_paths(Renderer& r, 
                              VertexSource& vs, 
                              const AttrStorage& as, 
                              const PathId& id,
                              unsigned num_paths,
                              double dx,
                              double dy)
        {
            for(unsigned i = 0; i < num_paths; i++)
            {
                reset();
                add_path(vs, dx, dy, id[i]);
                r.attribute(as[i]);
                render(r);
            }
        }



        //------------------------------------------------------------------------
        template<class Renderer, class Ctrl> void render_ctrl(Renderer& r, Ctrl& c)
        {
            unsigned i;
            for(i = 0; i < c.num_paths(); i++)
            {
                reset();
                add_path(c, i);
                r.attribute(c.color(i));
                render(r);
            }
        }


    private:
        rasterizer(const rasterizer&);
        const rasterizer& operator = (const rasterizer&);

    private:
        outline        m_outline;
        Scanline       m_scanline;
        GammaFunction  m_gamma;
        filling_rule_e m_filling_rule;
    };





    //----------------------------------------------------------------------------
    template<class S, class G> bool rasterizer<S, G>::hit_test(int tx, int ty)
    {
        if(m_outline.num_cells() == 0) return false;
        const cell* const* cells = m_outline.cells();
        if(cells == 0) return false;

        int x, y;
        int cover;
        int alpha;
        int area;

        cover = 0;
        const cell* cur_cell = *cells++;
        for(;;)
        {
            const cell* start_cell = cur_cell;

            int coord  = cur_cell->packed_coord;
            x = cur_cell->x;
            y = cur_cell->y;

            if(y > ty) return false;

            area   = start_cell->area;
            cover += start_cell->cover;

            while((cur_cell = *cells++) != 0)
            {
                if(cur_cell->packed_coord != coord) break;
                area  += cur_cell->area;
                cover += cur_cell->cover;
            }

            if(area)
            {
                alpha = calculate_alpha((cover << (poly_base_shift + 1)) - area);
                if(alpha)
                {
                    if(tx == x && ty == y) return true;
                }
                x++;
            }

            if(!cur_cell) break;

            if(cur_cell->x > x)
            {
                alpha = calculate_alpha(cover << (poly_base_shift + 1));
                if(alpha)
                {
                    if(ty == y && tx >= x && tx <= cur_cell->x) return true;
                }
            }
        }
        return false;
    }




}



#endif

