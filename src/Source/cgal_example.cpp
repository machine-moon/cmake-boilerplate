#include "cgal_example.h"
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Point_set_3.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/centroid.h>
#include <CGAL/convex_hull_2.h>
#include <iostream>
#include <list>
#include <random>
#include <vector>

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_2 Point_2;
typedef Kernel::Point_3 Point_3;
typedef Kernel::Triangle_2 Triangle_2;
typedef Kernel::Triangle_3 Triangle_3;
typedef CGAL::Polygon_2<Kernel> Polygon_2;
typedef CGAL::Delaunay_triangulation_2<Kernel> Delaunay_2;

namespace twiz
{

void show_cgal()
{
    std::cout << "\n=== CGAL COMPUTATIONAL GEOMETRY SHOWCASE ===" << std::endl;
    std::cout << "Computational Geometry Algorithms Library" << std::endl;
    std::cout << "Advanced geometric algorithms and data structures\n" << std::endl;

    Point_2 p(1.5, 2.7);
    Point_3 p3(1.0, 2.0, 3.0);
    std::cout << "CGAL 2D Point: " << p << std::endl;
    std::cout << "CGAL 3D Point: " << p3 << std::endl;
}

void computational_geometry_demo()
{
    std::cout << "\n--- Computational Geometry Demo ---" << std::endl;

    Point_2 a(0, 0);
    Point_2 b(4, 0);
    Point_2 c(2, 3);

    std::cout << "Triangle vertices:" << std::endl;
    std::cout << "  A: " << a << std::endl;
    std::cout << "  B: " << b << std::endl;
    std::cout << "  C: " << c << std::endl;

    Triangle_2 triangle(a, b, c);
    std::cout << "Triangle area: " << triangle.area() << std::endl;

    Point_2 centroid = CGAL::centroid(a, b, c);
    std::cout << "Triangle centroid: " << centroid << std::endl;

    Point_2 test_point(2, 1);
    std::cout << "Test point " << test_point << " is ";
    if (triangle.has_on_bounded_side(test_point))
        std::cout << "inside";
    else if (triangle.has_on_boundary(test_point))
        std::cout << "on boundary of";
    else
        std::cout << "outside";
    std::cout << " the triangle" << std::endl;

    Kernel::Line_2 line_ab(a, b);
    Kernel::Line_2 line_ac(a, c);

    auto result = CGAL::intersection(line_ab, line_ac);
    if (result)
    {
        if (const Point_2* intersection_point = std::get_if<Point_2>(&*result))
        {
            std::cout << "Line intersection at: " << *intersection_point << std::endl;
        }
    }

    std::cout << "Distance from A to B: " << CGAL::squared_distance(a, b) << " (squared)"
              << std::endl;

    Kernel::Circle_2 circumcircle(a, b, c);
    std::cout << "Circumcircle center: " << circumcircle.center() << std::endl;
    std::cout << "Circumcircle radius: " << sqrt(CGAL::to_double(circumcircle.squared_radius()))
              << std::endl;
}

void mesh_processing_demo()
{
    std::cout << "\n--- Basic Geometry Processing Demo ---" << std::endl;

    // Create a simple set of 3D points
    std::vector<Point_3> points_3d = {Point_3(0, 0, 0), Point_3(1, 0, 0), Point_3(0, 1, 0),
                                      Point_3(0, 0, 1), Point_3(1, 1, 1)};

    std::cout << "Created " << points_3d.size() << " 3D points" << std::endl;

    // Calculate centroid
    Point_3 centroid = CGAL::centroid(points_3d.begin(), points_3d.end(), CGAL::Dimension_tag<0>());
    std::cout << "Centroid: " << centroid << std::endl;
}

void convex_hull_demo()
{
    std::cout << "\n--- Convex Hull Demo ---" << std::endl;

    std::vector<Point_2> points;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-5.0, 5.0);

    for (int i = 0; i < 20; ++i)
    {
        points.push_back(Point_2(dis(gen), dis(gen)));
    }

    std::cout << "Generated " << points.size() << " random points:" << std::endl;
    for (size_t i = 0; i < std::min<size_t>(5, points.size()); ++i)
    {
        std::cout << "  " << points[i] << std::endl;
    }
    if (points.size() > 5)
        std::cout << "  ... and " << (points.size() - 5) << " more" << std::endl;

    std::vector<Point_2> hull_points;
    CGAL::convex_hull_2(points.begin(), points.end(), std::back_inserter(hull_points));

    std::cout << "\nConvex hull vertices (" << hull_points.size() << "):" << std::endl;
    for (const auto& p : hull_points)
    {
        std::cout << "  " << p << std::endl;
    }

    Polygon_2 hull_polygon(hull_points.begin(), hull_points.end());
    double hull_area = CGAL::to_double(hull_polygon.area());
    std::cout << "Convex hull area: " << std::abs(hull_area) << std::endl;

    int points_inside = 0;
    for (const auto& p : points)
    {
        if (hull_polygon.has_on_bounded_side(p))
            points_inside++;
    }
    std::cout << "Points strictly inside hull: " << points_inside << std::endl;
    std::cout << "Points on hull boundary: " << (points.size() - points_inside - hull_points.size())
              << std::endl;
}

void spatial_searching_demo()
{
    std::cout << "\n--- Spatial Searching Demo ---" << std::endl;

    std::vector<Point_2> points;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 10.0);

    for (int i = 0; i < 100; ++i)
    {
        points.push_back(Point_2(dis(gen), dis(gen)));
    }

    std::cout << "Created " << points.size() << " random points in [0,10] x [0,10]" << std::endl;

    Point_2 query_center(5.0, 5.0);
    double search_radius = 2.0;

    std::vector<Point_2> nearby_points;
    for (const auto& p : points)
    {
        double dist = sqrt(CGAL::to_double(CGAL::squared_distance(p, query_center)));
        if (dist <= search_radius)
        {
            nearby_points.push_back(p);
        }
    }

    std::cout << "Query center: " << query_center << std::endl;
    std::cout << "Search radius: " << search_radius << std::endl;
    std::cout << "Points within radius: " << nearby_points.size() << std::endl;

    if (!nearby_points.empty())
    {
        std::cout << "Sample nearby points:" << std::endl;
        for (size_t i = 0; i < std::min<size_t>(3, nearby_points.size()); ++i)
        {
            double dist =
                sqrt(CGAL::to_double(CGAL::squared_distance(nearby_points[i], query_center)));
            std::cout << "  " << nearby_points[i] << " (distance: " << dist << ")" << std::endl;
        }
    }

    Point_2 closest_point = points[0];
    double min_distance = sqrt(CGAL::to_double(CGAL::squared_distance(points[0], query_center)));

    for (const auto& p : points)
    {
        double dist = sqrt(CGAL::to_double(CGAL::squared_distance(p, query_center)));
        if (dist < min_distance)
        {
            min_distance = dist;
            closest_point = p;
        }
    }

    std::cout << "Closest point to query: " << closest_point << " (distance: " << min_distance
              << ")" << std::endl;
}

void polygon_operations_demo()
{
    std::cout << "\n--- Polygon Operations Demo ---" << std::endl;

    Polygon_2 square;
    square.push_back(Point_2(0, 0));
    square.push_back(Point_2(4, 0));
    square.push_back(Point_2(4, 4));
    square.push_back(Point_2(0, 4));

    std::cout << "Square vertices:" << std::endl;
    for (auto it = square.vertices_begin(); it != square.vertices_end(); ++it)
    {
        std::cout << "  " << *it << std::endl;
    }

    std::cout << "Square area: " << CGAL::to_double(square.area()) << std::endl;
    std::cout << "Square is simple: " << (square.is_simple() ? "yes" : "no") << std::endl;
    std::cout << "Square orientation: " << (square.is_counterclockwise_oriented() ? "CCW" : "CW")
              << std::endl;

    Polygon_2 triangle;
    triangle.push_back(Point_2(1, 1));
    triangle.push_back(Point_2(3, 1));
    triangle.push_back(Point_2(2, 3));

    std::cout << "\nTriangle vertices:" << std::endl;
    for (auto it = triangle.vertices_begin(); it != triangle.vertices_end(); ++it)
    {
        std::cout << "  " << *it << std::endl;
    }
    std::cout << "Triangle area: " << CGAL::to_double(triangle.area()) << std::endl;

    Point_2 test_points[] = {Point_2(2, 2), Point_2(1, 1), Point_2(5, 5)};

    for (const auto& test_point : test_points)
    {
        std::cout << "Point " << test_point << " vs square: ";
        if (square.has_on_bounded_side(test_point))
            std::cout << "inside";
        else if (square.has_on_boundary(test_point))
            std::cout << "on boundary";
        else
            std::cout << "outside";
        std::cout << std::endl;

        std::cout << "Point " << test_point << " vs triangle: ";
        if (triangle.has_on_bounded_side(test_point))
            std::cout << "inside";
        else if (triangle.has_on_boundary(test_point))
            std::cout << "on boundary";
        else
            std::cout << "outside";
        std::cout << std::endl;
    }
}

void triangulation_demo()
{
    std::cout << "\n--- Delaunay Triangulation Demo ---" << std::endl;

    Delaunay_2 triangulation;

    std::vector<Point_2> points;
    points.push_back(Point_2(0, 0));
    points.push_back(Point_2(1, 0));
    points.push_back(Point_2(0, 1));
    points.push_back(Point_2(1, 1));
    points.push_back(Point_2(0.5, 0.5));
    points.push_back(Point_2(0.2, 0.8));
    points.push_back(Point_2(0.8, 0.2));

    triangulation.insert(points.begin(), points.end());

    std::cout << "Inserted " << points.size() << " points" << std::endl;
    std::cout << "Number of vertices: " << triangulation.number_of_vertices() << std::endl;
    std::cout << "Number of faces: " << triangulation.number_of_faces() << std::endl;

    std::cout << "\nTriangulation faces:" << std::endl;
    int face_count = 0;
    for (auto fit = triangulation.finite_faces_begin();
         fit != triangulation.finite_faces_end() && face_count < 5; ++fit, ++face_count)
    {
        std::cout << "  Face " << face_count << ": ";
        for (int i = 0; i < 3; ++i)
        {
            std::cout << fit->vertex(i)->point();
            if (i < 2)
                std::cout << " - ";
        }
        std::cout << std::endl;
    }

    Point_2 query_point(0.3, 0.7);
    auto face = triangulation.locate(query_point);

    std::cout << "\nQuery point: " << query_point << std::endl;
    if (triangulation.is_infinite(face))
    {
        std::cout << "Point is outside the triangulation" << std::endl;
    }
    else
    {
        std::cout << "Point is in triangle with vertices:" << std::endl;
        for (int i = 0; i < 3; ++i)
        {
            std::cout << "  " << face->vertex(i)->point() << std::endl;
        }
    }

    auto nearest = triangulation.nearest_vertex(query_point);
    if (triangulation.number_of_vertices() > 0)
    {
        std::cout << "Nearest vertex: " << nearest->point() << std::endl;
        double dist = sqrt(CGAL::to_double(CGAL::squared_distance(query_point, nearest->point())));
        std::cout << "Distance: " << dist << std::endl;
    }
}

void run_cgal_geometry_suite()
{
    show_cgal();
    computational_geometry_demo();
    polygon_operations_demo();
    convex_hull_demo();
    triangulation_demo();
    spatial_searching_demo();
    mesh_processing_demo();

    std::cout << "\n=== CGAL GEOMETRY DEMO COMPLETE ===" << std::endl;
}

} // namespace twiz
