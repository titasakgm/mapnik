/*****************************************************************************
 *
 * This file is part of Mapnik (c++ mapping toolkit)
 *
 * Copyright (C) 2012 Artem Pavlenko
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *****************************************************************************/

#ifndef MAPNIK_AGG_HELPERS_HPP
#define MAPNIK_AGG_HELPERS_HPP

// mapnik
#include <mapnik/gamma_method.hpp>
#include <mapnik/stroke.hpp>            // for line_cap_e, line_join_e, etc


// agg 
#include "agg_gamma_functions.h"        // for gamma_power, gamma_linear, etc
#include "agg_math_stroke.h"            // for line_join_e::miter_join, etc
#include "agg_rasterizer_outline_aa.h"

namespace mapnik {

template <typename T0, typename T1>
void set_gamma_method(T0 const& obj, T1 & ras_ptr)
{
    switch (obj.get_gamma_method())
    {
    case GAMMA_POWER:
        ras_ptr->gamma(agg::gamma_power(obj.get_gamma()));
        break;
    case GAMMA_LINEAR:
        ras_ptr->gamma(agg::gamma_linear(0.0, obj.get_gamma()));
        break;
    case GAMMA_NONE:
        ras_ptr->gamma(agg::gamma_none());
        break;
    case GAMMA_THRESHOLD:
        ras_ptr->gamma(agg::gamma_threshold(obj.get_gamma()));
        break;
    case GAMMA_MULTIPLY:
        ras_ptr->gamma(agg::gamma_multiply(obj.get_gamma()));
        break;
    default:
        ras_ptr->gamma(agg::gamma_power(obj.get_gamma()));
    }
}

template <typename Stroke,typename PathType>
void set_join_caps(Stroke const& stroke_, PathType & stroke)
{
    line_join_e join=stroke_.get_line_join();
    switch (join)
    {
    case MITER_JOIN:
        stroke.generator().line_join(agg::miter_join);
        break;
    case MITER_REVERT_JOIN:
        stroke.generator().line_join(agg::miter_join);
        break;
    case ROUND_JOIN:
        stroke.generator().line_join(agg::round_join);
        break;
    default:
        stroke.generator().line_join(agg::bevel_join);
    }

    line_cap_e cap=stroke_.get_line_cap();
    switch (cap)
    {
    case BUTT_CAP:
        stroke.generator().line_cap(agg::butt_cap);
        break;
    case SQUARE_CAP:
        stroke.generator().line_cap(agg::square_cap);
        break;
    default:
        stroke.generator().line_cap(agg::round_cap);
    }
}


template <typename Stroke,typename Rasterizer>
void set_join_caps_aa(Stroke const& stroke_, Rasterizer & ras)
{

    line_join_e join=stroke_.get_line_join();
    switch (join)
    {
    case MITER_JOIN:
        ras.line_join(agg::outline_miter_accurate_join);
        break;
    case MITER_REVERT_JOIN:
        ras.line_join(agg::outline_no_join);
        break;
    case ROUND_JOIN:
        ras.line_join(agg::outline_round_join);
        break;
    default:
        ras.line_join(agg::outline_no_join);
    }

    line_cap_e cap=stroke_.get_line_cap();
    switch (cap)
    {
    case BUTT_CAP:
        ras.round_cap(false);
        break;
    case SQUARE_CAP:
        ras.round_cap(false);
        break;
    default:
        ras.round_cap(true);
    }
}

}

#endif //MAPNIK_AGG_HELPERS_HPP
