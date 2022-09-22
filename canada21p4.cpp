#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <array>

#define OPTIMIZED_SOL 1

typedef long long int_type;

// describes what counts as "covering" meteor - x axis
enum WHEN_REACHED_X
{
    STOP_AT_LEFT_SIDE_REACHED,
    STOP_AT_RIGHT_SIDE_REACHED
};
// describes what counts as "covering" meteor - y axis
enum WHEN_REACHED_Y
{
    STOP_AT_TOP_SIDE_REACHED,
    STOP_AT_BOTTOM_SIDE_REACHED
};

// Keeps track of location of meteor landing and time at which it will land
struct meteorLocation
{
    int_type x;
    int_type y;
    int_type time;

    meteorLocation(int_type t, int_type a, int_type b)
    {
        time = t;
        x = a;
        y = b;
    }
    meteorLocation() {}
    meteorLocation(const meteorLocation& t)
    {
        x = t.x;
        y = t.y;
        time = t.time;
    }

    void assign(meteorLocation t)
    {
        x = t.x;
        y = t.y;
    }
};
meteorLocation NO_EXIST(-1, -1, -1);

// Keeps track of all incoming meteors
struct meteorsList
{
    std::vector<meteorLocation> meteorLocations;

    void pushMeteorLocation(meteorLocation e)
    {
        meteorLocations.push_back(e);
    }
    std::size_t size()
    {
        return meteorLocations.size();
    }
    void print()
    {
        for (auto e : meteorLocations)
        {
            std::cout << e.x << ' ' << e.y << ' ' << e.time << '\n';
        }
    }
};

void input();
meteorLocation parseMeteorLine(std::string e);
int_type determineSideLengthOfTarp(meteorsList v, int_type speed);
int_type toNext(
    meteorLocation &coordsOfBottomLeft,
    meteorLocation current,
    WHEN_REACHED_X x_protocol,
    WHEN_REACHED_Y y_protocol,
    int_type size,
    std::size_t speed
);
std::pair<WHEN_REACHED_X, WHEN_REACHED_Y> determineXYProtocol(meteorLocation curr, meteorLocation next);

int main()
{
    input();
}

int_type determineSideLengthOfTarp(meteorsList v, int_type speed)
{
    // If tarp cannot move - tarp must cover all meteors from the start
    if (speed == 0)
    {
        auto minMaxX = std::minmax_element(v.meteorLocations.begin(), v.meteorLocations.end(), [](meteorLocation a, meteorLocation b)
                                           { return a.x < b.x; });

        auto minMaxY = std::minmax_element(v.meteorLocations.begin(), v.meteorLocations.end(), [](meteorLocation a, meteorLocation b)
                                           { return a.y < b.y; });

        int_type height = std::abs(minMaxY.first->y - minMaxY.second->y);
        int_type width = std::abs(minMaxX.first->x - minMaxX.second->x);

        return std::max(height, width);
    }
    else
    {
        meteorLocation bottomLeftCorner(v.meteorLocations[0]); // keeps track of bottom left corner
        int_type size = 0;                                     // keeps track of size of tarp
        for (std::size_t i = 0; i < v.size(); i++)
        {
            std::pair<WHEN_REACHED_X, WHEN_REACHED_Y> protocols;

            meteorLocation next;
            meteorLocation current = v.meteorLocations[i];

            // checks whether the next location to reach is the last meteor
            if (i < v.size() - 1)
            {
                next.assign(v.meteorLocations[i + 1]);
                protocols = determineXYProtocol(current, next);
            }
            else
            {
                next.assign(NO_EXIST);
            }

            size = toNext(
                bottomLeftCorner,
                current,
                protocols.first,
                protocols.second,
                size,
                speed
            );
        }

        return size;
    }
    return -1;
}

int_type toNext(
    meteorLocation &coordsOfBottomLeft,
    meteorLocation current,
    WHEN_REACHED_X x_protocol,
    WHEN_REACHED_Y y_protocol,
    int_type size,
    std::size_t speed
)
{
    // Tracks time used to move to next meteor
    int_type timeLeft = current.time - coordsOfBottomLeft.time;
    coordsOfBottomLeft.time = current.time;

#if OPTIMIZED_SOL

    std::size_t timeDecrement1 = 0;
    std::size_t timeDecrement2 = 0;

    // Movement along x axis
    if (!(current.x >= coordsOfBottomLeft.x && current.x <= coordsOfBottomLeft.x + size))
    {
        int_type whereToCheck = -1;
        switch (x_protocol)
        {
            // Indicates meteor should land on left side of tarp
            // This is in case meteor after this one is to the far right - tarp is closer - prevents needless expansion of tarp
            case STOP_AT_LEFT_SIDE_REACHED:
            {
                whereToCheck = coordsOfBottomLeft.x;
                break;
            }
            // Indicates meteor should land on right side of tarp
            // In case next meteor is to far left
            case STOP_AT_RIGHT_SIDE_REACHED:
            {
                whereToCheck = coordsOfBottomLeft.x + size;
                break;
            }
        }
        int_type inc = static_cast<int_type>(std::abs(current.x - whereToCheck) / speed);
        inc = inc > timeLeft ? timeLeft : inc;
        coordsOfBottomLeft.x += inc * speed - 2 * speed * inc * (current.x < whereToCheck);

        if (inc < timeLeft)
        {
            switch (x_protocol)
            {
                // Indicates meteor should land on left side of tarp
                // This is in case meteor after this one is to the far right - tarp is closer - prevents needless expansion of tarp
                case STOP_AT_LEFT_SIDE_REACHED:
                {
                    whereToCheck = coordsOfBottomLeft.x;
                    break;
                }
                // Indicates meteor should land on right side of tarp
                // In case next meteor is to far left
                case STOP_AT_RIGHT_SIDE_REACHED:
                {
                    whereToCheck = coordsOfBottomLeft.x + size;
                    break;
                }
            }

            int_type diff = std::abs(current.x - whereToCheck);
            coordsOfBottomLeft.x += diff - 2 * diff * (current.x < whereToCheck);
        }

        timeDecrement1 += inc + (inc < timeLeft);
    }

    // Movement along y axis
    if (!(current.y >= coordsOfBottomLeft.y && current.y <= coordsOfBottomLeft.y + size))
    {
        int_type whereToCheck = -1;
        switch (y_protocol)
        {
            // Indicates meteor should land on top side of tarp
            // In case next meteor is down below - tarp is closer
            case STOP_AT_TOP_SIDE_REACHED:
            {
                whereToCheck = coordsOfBottomLeft.y + size;
                break;
            }
            // Indicates meteor should land on bottom side of tarp
            // In case next meteor is above
            case STOP_AT_BOTTOM_SIDE_REACHED:
            {
                whereToCheck = coordsOfBottomLeft.y;
                break;
            }
        }

        int_type inc = static_cast<int_type>(std::abs(current.y - whereToCheck) / speed);
        inc = inc > timeLeft ? timeLeft : inc;
        coordsOfBottomLeft.y += inc * speed - 2 * speed * inc * (current.y < whereToCheck);
        // std::cout << "inc_y: " << inc << '\n';
        // std::cout << "timeLeft: " << timeLeft << '\n';
        // std::cout << "decrement_y: " << inc * speed - 2 * speed * inc * (current.y < whereToCheck) << '\n';

        if (inc < timeLeft)
        {
            switch (y_protocol)
            {
                // Indicates meteor should land on top side of tarp
                // In case next meteor is down below - tarp is closer
                case STOP_AT_TOP_SIDE_REACHED:
                {
                    whereToCheck = coordsOfBottomLeft.y + size;
                    break;
                }
                // Indicates meteor should land on bottom side of tarp
                // In case next meteor is above
                case STOP_AT_BOTTOM_SIDE_REACHED:
                {
                    whereToCheck = coordsOfBottomLeft.y;
                    break;
                }
            }

            int_type diff = std::abs(current.y - whereToCheck);
            coordsOfBottomLeft.y += diff - 2 * diff * (current.y < whereToCheck);
        }

        timeDecrement2 += inc + (inc < timeLeft);
    }

    timeLeft -= std::max(timeDecrement1, timeDecrement2);

    //std::cout << "1: " << coordsOfBottomLeft.x << ' ' << coordsOfBottomLeft.y << '\n';

    int_type amountDecrementedX = std::abs(current.x - coordsOfBottomLeft.x);
    int_type amountDecrementedY = std::abs(current.y - coordsOfBottomLeft.y);
    
    std::size_t height = 0;
    std::size_t width = 0;
    bool mustKeepDecrementing = false;

    if (!(current.x >= coordsOfBottomLeft.x && current.x <= coordsOfBottomLeft.x + size))
    {
        //Add difference between current position and meteor position to width
        width += amountDecrementedX;
        //If meteor is to the left, move tarp to the left
        if (current.x < coordsOfBottomLeft.x)
        {
            coordsOfBottomLeft.x -= amountDecrementedX;
        }
        //If meteor is below, move tarp down
        if (current.y < coordsOfBottomLeft.y)
        {
            mustKeepDecrementing = amountDecrementedY > amountDecrementedX;
            coordsOfBottomLeft.y -= mustKeepDecrementing ? amountDecrementedX : amountDecrementedY;
        }
    }
    size += width;

    if (!(current.y >= coordsOfBottomLeft.y && current.y <= coordsOfBottomLeft.y + size))
    {
        height += amountDecrementedY;
        if (mustKeepDecrementing)
        {
            coordsOfBottomLeft.y -= amountDecrementedY - amountDecrementedX;
        }
    }

    size -= width;
    size += std::max(height, width);

#else

    //Go to current
    while (timeLeft > 0)
    {
        //Movement along x axis
        if (!(current.x >= coordsOfBottomLeft.x && current.x <= coordsOfBottomLeft.x + size))
        {
            int_type whereToCheck;
            switch (x_protocol)
            {
                //Indicates meteor should land on left side of tarp
                //This is in case meteor after this one is to the far right - tarp is closer - prevents needless expansion of tarp
                case STOP_AT_LEFT_SIDE_REACHED:
                {
                    whereToCheck = coordsOfBottomLeft.x;
                    break;
                }
                //Indicates meteor should land on right side of tarp
                //In case next meteor is to far left
                case STOP_AT_RIGHT_SIDE_REACHED:
                {
                    whereToCheck = coordsOfBottomLeft.x + size;
                    break;
                }
            }
            if (std::abs(current.x - whereToCheck) >= speed)
            {
                coordsOfBottomLeft.x += speed - 2 * speed * (current.x < whereToCheck);
            }
            else
            {
                int_type diff = std::abs(current.x - whereToCheck);
                coordsOfBottomLeft.x += diff - 2 * diff * (current.x < whereToCheck);
            }
        }

        //Movement along y axis
        if (!(current.y >= coordsOfBottomLeft.y && current.y <= coordsOfBottomLeft.y + size))
        {
            int_type whereToCheck;
            switch (x_protocol)
            {
                //Indicates meteor should land on top side of tarp
                //In case next meteor is down below - tarp is closer
                case STOP_AT_TOP_SIDE_REACHED:
                {
                    whereToCheck = coordsOfBottomLeft.y + size;
                    break;
                }
                //Indicates meteor should land on bottom side of tarp
                //In case next meteor is above
                case STOP_AT_BOTTOM_SIDE_REACHED:
                {
                    whereToCheck = coordsOfBottomLeft.y;
                    break;
                }
            }
            if (std::abs(current.y - whereToCheck) >= speed)
            {
                coordsOfBottomLeft.y += speed - 2 * speed * (current.y < whereToCheck);
            }
            else
            {
                int_type diff = std::abs(current.y - whereToCheck);
                coordsOfBottomLeft.y += diff - 2 * diff * (current.y < whereToCheck);
            }
        }
        timeLeft--;
    }

    while (!(current.x >= coordsOfBottomLeft.x && current.x <= coordsOfBottomLeft.x + size))
    {
        size++;
        if (current.x < coordsOfBottomLeft.x)
        {
            coordsOfBottomLeft.x--;
        }
        if (current.y < coordsOfBottomLeft.y)
        {
            coordsOfBottomLeft.y--;
        }
    }
    while (!(current.y >= coordsOfBottomLeft.y && current.y <= coordsOfBottomLeft.y + size))
    {
        size++;
        if (current.y < coordsOfBottomLeft.y)
        {
            coordsOfBottomLeft.y--;
        }
    }

#endif

    //std::cout << "2: " << coordsOfBottomLeft.x << ' ' << coordsOfBottomLeft.y << '\n';

    //std::cout << "size: " << size << '\n';

    return size;
}

void input()
{
    std::string in;
    std::getline(std::cin, in);

    std::string::size_type n, K;
    std::string::size_type space = in.find(' ');
    n = std::stoull(in.substr(0, space));
    K = std::stoull(in.substr(space + 1));

    meteorsList allInputs;

    std::vector<std::string> test;
    for (std::string::size_type i = 0; i < n; i++)
    {
        std::string line;
        std::getline(std::cin, line);
        test.push_back(line);

        allInputs.pushMeteorLocation(parseMeteorLine(line));
    }

    std::cout << determineSideLengthOfTarp(allInputs, K) << '\n';
}

meteorLocation parseMeteorLine(std::string e)
{
    std::size_t lines[3] = {0, 0, 0};

    int j = 0;
    for (std::size_t i = 0; i < e.length() && j < 3; i++)
    {
        if (e[i] == ' ')
        {
            lines[j] /= 10;
            j++;
        }
        else
        {
            lines[j] += e[i] - '0';
            lines[j] *= 10;
        }
    }
    lines[2] /= 10;
    return meteorLocation(lines[0], lines[1], lines[2]);
}

std::pair<WHEN_REACHED_X, WHEN_REACHED_Y> determineXYProtocol(meteorLocation curr, meteorLocation next)
{
    WHEN_REACHED_X x;
    WHEN_REACHED_Y y;
    if (curr.y < next.y)
    {
        y = STOP_AT_TOP_SIDE_REACHED;
    }
    else if (curr.y >= next.y)
    {
        y = STOP_AT_BOTTOM_SIDE_REACHED;
    }
    if (curr.x < next.x)
    {
        x = STOP_AT_RIGHT_SIDE_REACHED;
    }
    else if (curr.x >= next.x)
    {
        x = STOP_AT_LEFT_SIDE_REACHED;
    }

    return {x, y};
}