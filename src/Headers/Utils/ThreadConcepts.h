#pragma once
#include <concepts>

template<typename T>
concept MetricsMemberPresent = requires
{
    &T::m_metrics;
};

template<typename T, typename U>
concept IsValidMetricsMember = std::same_as<U, decltype(T::m_metrics)>;

template<typename Properties, typename Metrics, typename PropertiesBase, typename MetricsBase>
concept DerivedFromPropertiesAndMetrics = std::derived_from<Properties, PropertiesBase> && std::derived_from<Metrics, MetricsBase>;

template<typename Properties, typename Metrics, typename PropertiesBase, typename MetricsBase>
concept ThreadCompatible = MetricsMemberPresent<Properties> && IsValidMetricsMember<Properties, Metrics> && DerivedFromPropertiesAndMetrics<Properties, Metrics, PropertiesBase, MetricsBase>;
