#version 330 core

uniform vec2 bl;
uniform vec2 wh;
uniform float border_radius;
uniform float width;

in vec2 pos;

out vec3 color;

float distance_squared(vec2 a, vec2 b) {
    return pow(a.x - b.x, 2) + pow(a.y - b.y, 2);
}

void main()
{
    bool curve_check_correct = false;
    if (border_radius > 0) {
        vec2 directions[4] = vec2[4](vec2(-1, 1), vec2(1, 1), vec2(-1, -1), vec2(1, -1));
        vec2 check_points[4] = vec2[4](
            bl + vec2(0, wh.y) + border_radius * -directions[0], 
            bl + wh + border_radius * -directions[1],
            bl + border_radius * -directions[2],
            bl + vec2(wh.x, 0) + border_radius * -directions[3]
        );

        for (int i = 0; i < 4; i++) {
            vec2 dir = pos - check_points[i];
            if (sign(dir.x) == sign(directions[i].x) && sign(dir.y) == sign(directions[i].y) && distance_squared(pos, check_points[i]) > pow(border_radius, 2)) {
                discard;
            }
        }
        if (width > 0) {
            bool checkable = false;
            for (int i = 0; i < 4; i++) {
                vec2 dir = pos - check_points[i];
                if (sign(dir.x) == sign(directions[i].x) && sign(dir.y) == sign(directions[i].y)) {
                    checkable = true;
                }
            }
            if (checkable) {
                for (int i = 0; i < 4; i++) {
                    vec2 dir = pos - check_points[i];
                    if (sign(dir.x) == sign(directions[i].x) && sign(dir.y) == sign(directions[i].y) && distance_squared(pos, check_points[i]) < pow(border_radius - width, 2)) {
                        discard;
                    }
                }
                curve_check_correct = true;
            }
        }
    }
    if (!curve_check_correct && width > 0) {
        vec2 exclude_rect_bl = bl + vec2(width);
        vec2 exclude_rect_wh = wh - vec2(width) * 2;
        vec2 exclude_rect_tr = exclude_rect_bl + exclude_rect_wh;
        if (pos.x > exclude_rect_bl.x && pos.y > exclude_rect_bl.y && pos.x < exclude_rect_tr.x && pos.y < exclude_rect_tr.y) {
            discard;
        }
    }
    color = vec3(1, 1, 1);
}