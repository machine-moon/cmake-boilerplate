#include "Examples/cgal.h"
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Point_set_3.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/centroid.h>
#include <CGAL/convex_hull_2.h>
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <random>
#include <variant>
#include <vector>

using Kernel = CGAL::Simple_cartesian<double>;
using Point_2 = Kernel::Point_2;
using Point_3 = Kernel::Point_3;
using Triangle_2 = Kernel::Triangle_2;
using Triangle_3 = Kernel::Triangle_3;
using Polygon_2 = CGAL::Polygon_2<Kernel>;
using Delaunay_2 = CGAL::Delaunay_triangulation_2<Kernel>;

namespace Twiz
{

    void ShowCgal()
    {
        std::cout << "\n=== CGAL COMPUTATIONAL GEOMETRY SHOWCASE ===" << '\n';
        std::cout << "Computational Geometry Algorithms Library" << '\n';
        std::cout << "Advanced geometric algorithms and data structures\n" << '\n';

        Point_2 const poinT2(1.5, 2.7);
        Point_3 const poinT3(1.0, 2.0, 3.0);
        std::cout << "CGAL 2D Point: " << poinT2 << '\n';
        std::cout << "CGAL 3D Point: " << poinT3 << '\n';
    }

    void ComputationalGeometryDemo()
    {
        std::cout << "\n--- Computational Geometry Demo ---" << '\n';

        Point_2 const pointa(0, 0);
        Point_2 const pointb(4, 0);
        Point_2 const pointc(2, 3);

        std::cout << "Triangle vertices:" << '\n';
        std::cout << "  A: " << pointa << '\n';
        std::cout << "  B: " << pointb << '\n';
        std::cout << "  C: " << pointc << '\n';

        Triangle_2 const triangle(pointa, pointb, pointc);
        std::cout << "Triangle area: " << triangle.area() << '\n';

        Point_2 const centroid = CGAL::centroid(pointa, pointb, pointc);
        std::cout << "Triangle centroid: " << centroid << '\n';

        Point_2 const testPoint(2, 1);
        std::cout << "Test point " << testPoint << " is ";
        if (triangle.has_on_bounded_side(testPoint))
        {
            std::cout << "inside";
        }
        else if (triangle.has_on_boundary(testPoint))
        {
            std::cout << "on boundary of";
        }
        else
        {
            std::cout << "outside";
        }
        std::cout << " the triangle" << '\n';

        Kernel::Line_2 const lineAb(pointa, pointb);
        Kernel::Line_2 const lineAc(pointa, pointc);

        auto result = CGAL::intersection(lineAb, lineAc);
        if (result)
        {
            if (const Point_2* intersectionPoint = std::get_if<Point_2>(&*result))
            {
                std::cout << "Line intersection at: " << *intersectionPoint << '\n';
            }
        }

        std::cout << "Distance from A to B: " << CGAL::squared_distance(pointa, pointb) << " (squared)" << '\n';

        Kernel::Circle_2 const circumcircle(pointa, pointb, pointc);
        std::cout << "Circumcircle center: " << circumcircle.center() << '\n';
        std::cout << "Circumcircle radius: " << sqrt(CGAL::to_double(circumcircle.squared_radius())) << '\n';
    }

    void MeshProcessingDemo()
    {
        std::cout << "\n--- Basic Geometry Processing Demo ---" << '\n';

        // Create a simple set of 3D points
        std::vector<Point_3> points3d = {Point_3(0, 0, 0), Point_3(1, 0, 0), Point_3(0, 1, 0), Point_3(0, 0, 1), Point_3(1, 1, 1)};

        std::cout << "Created " << points3d.size() << " 3D points" << '\n';

        // Calculate centroid
        Point_3 const centroid = CGAL::centroid(points3d.begin(), points3d.end(), CGAL::Dimension_tag<0>());
        std::cout << "Centroid: " << centroid << '\n';
    }

    void ConvexHullDemo()
    {
        std::cout << "\n--- Convex Hull Demo ---" << '\n';

        std::vector<Point_2> points;
        std::random_device randomDevice;
        std::mt19937 gen(randomDevice());
        std::uniform_real_distribution<> dis(-5.0, 5.0);

        points.reserve(20);
        for (int i = 0; i < 20; ++i)
        {
            points.emplace_back(dis(gen), dis(gen));
        }

        std::cout << "Generated " << points.size() << " random points:" << '\n';
        for (size_t i = 0; i < std::min<size_t>(5, points.size()); ++i)
        {
            std::cout << "  " << points[i] << '\n';
        }
        if (points.size() > 5)
        {
            std::cout << "  ... and " << (points.size() - 5) << " more" << '\n';
        }

        std::vector<Point_2> hullPoints;
        CGAL::convex_hull_2(points.begin(), points.end(), std::back_inserter(hullPoints));

        std::cout << "\nConvex hull vertices (" << hullPoints.size() << "):" << '\n';
        for (const auto& point : hullPoints)
        {
            std::cout << "  " << point << '\n';
        }

        Polygon_2 const hullPolygon(hullPoints.begin(), hullPoints.end());
        double const hullArea = CGAL::to_double(hullPolygon.area());
        std::cout << "Convex hull area: " << std::abs(hullArea) << '\n';

        int pointsInside = 0;
        for (const auto& point : points)
        {
            if (hullPolygon.has_on_bounded_side(point))
            {
                pointsInside++;
            }
        }
        std::cout << "Points strictly inside hull: " << pointsInside << '\n';
        std::cout << "Points on hull boundary: " << (points.size() - pointsInside - hullPoints.size()) << '\n';
    }

    void SpatialSearchingDemo()
    {
        std::cout << "\n--- Spatial Searching Demo ---" << '\n';

        std::vector<Point_2> points;
        std::random_device randomDevice;
        std::mt19937 gen(randomDevice());
        std::uniform_real_distribution<> dis(0.0, 10.0);

        points.reserve(100);
        for (int i = 0; i < 100; ++i)
        {
            points.emplace_back(dis(gen), dis(gen));
        }

        std::cout << "Created " << points.size() << " random points in [0,10] x [0,10]" << '\n';

        Point_2 const queryCenter(5.0, 5.0);
        double const searchRadius = 2.0;

        std::vector<Point_2> nearbyPoints;
        for (const auto& point : points)
        {
            double const dist = sqrt(CGAL::to_double(CGAL::squared_distance(point, queryCenter)));
            if (dist <= searchRadius)
            {
                nearbyPoints.push_back(point);
            }
        }

        std::cout << "Query center: " << queryCenter << '\n';
        std::cout << "Search radius: " << searchRadius << '\n';
        std::cout << "Points within radius: " << nearbyPoints.size() << '\n';

        if (!nearbyPoints.empty())
        {
            std::cout << "Sample nearby points:" << '\n';
            for (size_t i = 0; i < std::min<size_t>(3, nearbyPoints.size()); ++i)
            {
                double const dist = sqrt(CGAL::to_double(CGAL::squared_distance(nearbyPoints[i], queryCenter)));
                std::cout << "  " << nearbyPoints[i] << " (distance: " << dist << ")" << '\n';
            }
        }

        Point_2 closestPoint = points[0];
        double minDistance = sqrt(CGAL::to_double(CGAL::squared_distance(points[0], queryCenter)));

        for (const auto& point : points)
        {
            double const dist = sqrt(CGAL::to_double(CGAL::squared_distance(point, queryCenter)));
            if (dist < minDistance)
            {
                minDistance = dist;
                closestPoint = point;
            }
        }

        std::cout << "Closest point to query: " << closestPoint << " (distance: " << minDistance << ")" << '\n';
    }

    void PolygonOperationsDemo()
    {
        std::cout << "\n--- Polygon Operations Demo ---" << '\n';

        Polygon_2 square;
        square.push_back(Point_2(0, 0));
        square.push_back(Point_2(4, 0));
        square.push_back(Point_2(4, 4));
        square.push_back(Point_2(0, 4));

        std::cout << "Square vertices:" << '\n';
        for (auto it = square.vertices_begin(); it != square.vertices_end(); ++it)
        {
            std::cout << "  " << *it << '\n';
        }

        std::cout << "Square area: " << CGAL::to_double(square.area()) << '\n';
        std::cout << "Square is simple: " << (square.is_simple() ? "yes" : "no") << '\n';
        std::cout << "Square orientation: " << (square.is_counterclockwise_oriented() ? "CCW" : "CW") << '\n';

        Polygon_2 triangle;
        triangle.push_back(Point_2(1, 1));
        triangle.push_back(Point_2(3, 1));
        triangle.push_back(Point_2(2, 3));

        std::cout << "\nTriangle vertices:" << '\n';
        for (auto it = triangle.vertices_begin(); it != triangle.vertices_end(); ++it)
        {
            std::cout << "  " << *it << '\n';
        }
        std::cout << "Triangle area: " << CGAL::to_double(triangle.area()) << '\n';

        Point_2 const testPoints[] = {Point_2(2, 2), Point_2(1, 1), Point_2(5, 5)};

        for (const auto& testPoint : testPoints)
        {
            std::cout << "Point " << testPoint << " vs square: ";
            if (square.has_on_bounded_side(testPoint))
            {
                std::cout << "inside";
            }
            else if (square.has_on_boundary(testPoint))
            {
                std::cout << "on boundary";
            }
            else
            {
                std::cout << "outside";
            }
            std::cout << '\n';

            std::cout << "Point " << testPoint << " vs triangle: ";
            if (triangle.has_on_bounded_side(testPoint))
            {
                std::cout << "inside";
            }
            else if (triangle.has_on_boundary(testPoint))
            {
                std::cout << "on boundary";
            }
            else
            {
                std::cout << "outside";
            }
            std::cout << '\n';
        }
    }

    void TriangulationDemo()
    {
        std::cout << "\n--- Delaunay Triangulation Demo ---" << '\n';

        Delaunay_2 triangulation;

        std::vector<Point_2> points;
        points.emplace_back(0, 0);
        points.emplace_back(1, 0);
        points.emplace_back(0, 1);
        points.emplace_back(1, 1);
        points.emplace_back(0.5, 0.5);
        points.emplace_back(0.2, 0.8);
        points.emplace_back(0.8, 0.2);

        triangulation.insert(points.begin(), points.end());

        std::cout << "Inserted " << points.size() << " points" << '\n';
        std::cout << "Number of vertices: " << triangulation.number_of_vertices() << '\n';
        std::cout << "Number of faces: " << triangulation.number_of_faces() << '\n';

        std::cout << "\nTriangulation faces:" << '\n';
        int faceCount = 0;
        for (auto fit = triangulation.finite_faces_begin(); fit != triangulation.finite_faces_end() && faceCount < 5; ++fit, ++faceCount)
        {
            std::cout << "  Face " << faceCount << ": ";
            for (int i = 0; i < 3; ++i)
            {
                std::cout << fit->vertex(i)->point();
                if (i < 2)
                {
                    std::cout << " - ";
                }
            }
            std::cout << '\n';
        }

        Point_2 const queryPoint(0.3, 0.7);
        auto face = triangulation.locate(queryPoint);

        std::cout << "\nQuery point: " << queryPoint << '\n';
        if (triangulation.is_infinite(face))
        {
            std::cout << "Point is outside the triangulation" << '\n';
        }
        else
        {
            std::cout << "Point is in triangle with vertices:" << '\n';
            for (int i = 0; i < 3; ++i)
            {
                std::cout << "  " << face->vertex(i)->point() << '\n';
            }
        }

        auto nearest = triangulation.nearest_vertex(queryPoint);
        if (triangulation.number_of_vertices() > 0)
        {
            std::cout << "Nearest vertex: " << nearest->point() << '\n';
            double const dist = sqrt(CGAL::to_double(CGAL::squared_distance(queryPoint, nearest->point())));
            std::cout << "Distance: " << dist << '\n';
        }
    }

    void RunCgalGeometrySuite()
    {
        ShowCgal();
        ComputationalGeometryDemo();
        PolygonOperationsDemo();
        ConvexHullDemo();
        TriangulationDemo();
        SpatialSearchingDemo();
        MeshProcessingDemo();

        std::cout << "\n=== CGAL GEOMETRY DEMO COMPLETE ===" << '\n';
    }

} // namespace Twiz
