//----------------------------------------------------------------------------
// Anti-Grain Geometry - Version 2.0 
// Copyright (C) 2002 Maxim Shemanarev (McSeem)
//
// Permission to copy, use, modify, sell and distribute this software 
// is granted provided this copyright notice appears in all copies. 
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//
//----------------------------------------------------------------------------
// Contact: mcseem@antigrain.com
//          mcseemagg@yahoo.com
//          http://www.antigrain.com
//----------------------------------------------------------------------------
//
// Class path_storage
//
//----------------------------------------------------------------------------
#include <string.h>
#include <math.h>
#include "thirdparty/common/agg/include/agg_path_storage.h"
#include "thirdparty/common/agg/include/agg_math.h"


namespace agg
{

    //------------------------------------------------------------------------
    path_storage::~path_storage()
    {
        if(m_total_blocks)
        {
            double** coord_blk = m_coord_blocks + m_total_blocks - 1;
            while(m_total_blocks--)
            {
                delete [] *coord_blk;
                --coord_blk;
            }
            delete [] m_coord_blocks;
        }
    }


    //------------------------------------------------------------------------
    path_storage::path_storage() :
        m_total_vertices(0),
        m_total_blocks(0),
        m_max_blocks(0),
        m_coord_blocks(0),
        m_cmd_blocks(0),
        m_iterator(0)
    {
    }


    //------------------------------------------------------------------------
    path_storage::path_storage(const path_storage& ps) : 
        m_total_vertices(0),
        m_total_blocks(0),
        m_max_blocks(0),
        m_coord_blocks(0),
        m_cmd_blocks(0),
        m_iterator(0)
    {
        copy_from(ps);
    }


    //------------------------------------------------------------------------
    void path_storage::remove_all()
    {
        m_total_vertices = 0;
        m_iterator = 0;
    }


    //------------------------------------------------------------------------
    void path_storage::copy_from(const path_storage& ps)
    {
        remove_all();
        unsigned i;
        for(i = 0; i < ps.total_vertices(); i++)
        {
            double x, y;
            unsigned cmd = ps.vertex(i, &x, &y);
            add_vertex(x, y, cmd);
        }
    }


    //------------------------------------------------------------------------
    void path_storage::allocate_block(unsigned nb)
    {
        if(nb >= m_max_blocks) 
        {
            double** new_coords = 
                new double* [(m_max_blocks + block_pool) * 2];

            unsigned char** new_cmds = 
                (unsigned char**)(new_coords + m_max_blocks + block_pool);

            if(m_coord_blocks)
            {
                memcpy(new_coords, 
                       m_coord_blocks, 
                       m_max_blocks * sizeof(double*));

                memcpy(new_cmds, 
                       m_cmd_blocks, 
                       m_max_blocks * sizeof(unsigned char*));

                delete [] m_coord_blocks;
            }
            m_coord_blocks = new_coords;
            m_cmd_blocks = new_cmds;
            m_max_blocks += block_pool;
        }
        m_coord_blocks[nb] = 
            new double [block_size * 2 + 
                        block_size / 
                        (sizeof(double) / sizeof(unsigned char))];

        m_cmd_blocks[nb]  = 
            (unsigned char*)(m_coord_blocks[nb] + block_size * 2);

        m_total_blocks++;
    }


    //------------------------------------------------------------------------
    void path_storage::rewind(unsigned id)
    {
        m_iterator = id; 
    }

    //------------------------------------------------------------------------
    void path_storage::curve3(double x_ctrl, double y_ctrl, 
                              double x_to,   double y_to)
    {
        add_vertex(x_ctrl, y_ctrl, path_cmd_curve3);
        add_vertex(x_to,   y_to,   path_cmd_curve3);
    }


    //------------------------------------------------------------------------
    void path_storage::curve4(double x_ctrl1, double y_ctrl1, 
                                     double x_ctrl2, double y_ctrl2, 
                                     double x_to,    double y_to)
    {
        add_vertex(x_ctrl1, y_ctrl1, path_cmd_curve4);
        add_vertex(x_ctrl2, y_ctrl2, path_cmd_curve4);
        add_vertex(x_to,    y_to,    path_cmd_curve4);
    }



    //------------------------------------------------------------------------
    void path_storage::close_polygon()
    {
        if(m_total_vertices)
        {
            unsigned char* cmd_ptr = 
                m_cmd_blocks[(m_total_vertices - 1) >> block_shift] + 
                ((m_total_vertices - 1) & block_mask);

            if(!is_end_poly(*cmd_ptr))
            {
                *cmd_ptr |= path_flags_close;
            }
        }
    }



    //------------------------------------------------------------------------
    unsigned path_storage::add_new_path()
    {
        if(m_total_vertices)
        {
            add_vertex(0.0, 0.0, path_cmd_stop);
        }
        return m_total_vertices;
    }


    //------------------------------------------------------------------------
    unsigned path_storage::perceive_polygon_orientation(unsigned idx, 
                                                        double xs, 
                                                        double ys)
    {
        unsigned i;
        double sum = 0.0;
        double x = xs;
        double y = ys;
        double x1, y1;

        for(i = idx + 1; i < m_total_vertices; i++)
        {
            if(is_end_poly(vertex(i, &x1, &y1))) break;
            sum += x * y1 - y * x1;
            x = x1;
            y = y1;
        }
        sum += x * ys - y * xs;

        unsigned char* cmd_ptr = m_cmd_blocks[idx >> block_shift] + (idx & block_mask);
        *cmd_ptr = (unsigned char) (sum < 0.0) ? 
                                    set_cw(*cmd_ptr) : 
                                    set_ccw(*cmd_ptr);
        return i - idx - 1;
    }



    //------------------------------------------------------------------------
    int path_storage::perceive_orientation(unsigned start)
    {
        unsigned i;
        double x, y;
        int balance = 0;

        for(i = start; i < m_total_vertices; i++)
        {
            unsigned cmd = vertex(i, &x, &y);
            if(is_move_to(cmd))
            {
                int n = perceive_polygon_orientation(i, x, y);
                unsigned cmd = m_cmd_blocks[i >> block_shift][i & block_mask];
                if(is_ccw(cmd)) balance++;
                if(is_cw(cmd))  balance--;
                i += n;
            }
            if(is_stop(cmd)) break;
        }
        return balance;
    }



    //------------------------------------------------------------------------
    void path_storage::reverse_orientation(unsigned start, unsigned end)
    {
        unsigned i;
        unsigned tmp_cmd = m_cmd_blocks[start >> block_shift][start & block_mask];
        
        // Shift all attributes to one position
        for(i = start; i < end; i++)
        {
            m_cmd_blocks[i >> block_shift][i & block_mask] = 
                m_cmd_blocks[(i + 1) >> block_shift][(i + 1) & block_mask];
        }

        // Assign move_to to the ending cmd
        m_cmd_blocks[end >> block_shift][end & block_mask] = (unsigned char)tmp_cmd;

        // Reverse the polygon
        while(end > start)
        {
            unsigned start_nb = start >> block_shift;
            unsigned end_nb   = end   >> block_shift;
            double* start_ptr = m_coord_blocks[start_nb] + ((start & block_mask) << 1);
            double* end_ptr   = m_coord_blocks[end_nb]   + ((end   & block_mask) << 1);
            double tmp_xy;

            tmp_xy       = *start_ptr;
            *start_ptr++ = *end_ptr;
            *end_ptr++   = tmp_xy;

            tmp_xy       = *start_ptr;
            *start_ptr   = *end_ptr;
            *end_ptr     = tmp_xy;

            tmp_cmd = m_cmd_blocks[start_nb][start & block_mask];
            m_cmd_blocks[start_nb][start & block_mask] = m_cmd_blocks[end_nb][end & block_mask];
            m_cmd_blocks[end_nb][end & block_mask] = (unsigned char)tmp_cmd;

            ++start;
            --end;
        }


    }





    //------------------------------------------------------------------------
    void path_storage::arrange_orientation(unsigned start,
                                           bool perception_flag, 
                                           path_flags_e new_orientation)
    {
        int balance = 0;
        if(perception_flag)
        {
            balance = perceive_orientation(start);
            if(!is_oriented(new_orientation))
            {
                new_orientation = (balance >= 0) ? path_flags_ccw : path_flags_cw;
            }
        }

        if(is_oriented(new_orientation))
        {
            unsigned i;
            path_flags_e of = path_flags_none;
            unsigned start_i = 0;

            for(i = start; i < m_total_vertices; i++)
            {
                unsigned char cmd = m_cmd_blocks[i >> block_shift][i & block_mask];

                if(is_stop(cmd)) break;

                if(is_move_to(cmd))
                {
                    if(i > start_i && is_oriented(of) && of != new_orientation)
                    {
                        reverse_orientation(start_i, i - 1);
                    }
                    start_i = i;
                    of = get_orientation(cmd);
                }
            }
            if(i > start_i && is_oriented(of) && of != new_orientation)
            {
                reverse_orientation(start_i, i - 1);
            }
        }
    }


    //------------------------------------------------------------------------
    void path_storage::add_poly(const double* vertices, unsigned num,
                                path_flags_e flags)
    {
        if(num > 1)
        {
            move_to(*vertices, *(vertices + 1), flags);
            vertices += 2;
            while(--num)
            {
                line_to(*vertices, *(vertices + 1));
                vertices += 2;
            }
        }
    }




}

