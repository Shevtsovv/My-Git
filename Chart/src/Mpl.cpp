#include <QtChart.h>
/*Пеобразовать массив реальных данных под масштаб окна линейным преобразованием*/
vec Qt::ScalePerform(const vec& u) const
{
    /*нельзя передавать нулевой вектор, поскольку иначе min = max!*/
    /*проверка на нулевой вектор, он непустой, учитываем это, true - нулевой, false - ненулевой*/
    auto lambda = [](const vec& v)->bool
    {
        for(std::size_t i = 0; i < v.size(); ++i)
        {
            if(v[i] != 0){
                return false;
            }
        }
        return true;
    };
    bool singular = lambda(u);
    if(singular)
    {
        throw std::invalid_argument("Incorrect data vector : vector is zero!");
    }
    vec u_scale = u;
    /*Поиск минимального и максимального значения в контейнеров*/
    const auto [min, max] = std::minmax_element(u.begin(), u.end());
    std::size_t window_len = qt_->getSize().x;
    /*дополнительный отступ*/
    double sigma = (*max - *min) * 0.25;
    for(std::size_t i = 0; i < u.size(); ++i)
    {
        double u_dest = (u[i] - *min + sigma) * (window_len) / (*max - *min + 2 * sigma);
        u_scale[i] = u_dest;
    }
    return u_scale;
}
/*Рассчитать положение координатных линий сетки по входному массиву оси*/
std::vector<sf::VertexArray> Qt::CreateGrid(const vec& u, bool horizontal) const
{
    vec coord = ScalePerform(u);
    std::size_t window_len = qt_->getSize().x;
    const int num_lines = 10;
    /*Массив хранения для сетки*/
    sf::VertexArray grid(sf::PrimitiveType::Lines, num_lines * 2);
    Qt::Color grid_color({220, 220, 220});
    for(int i = 0; i < num_lines; ++i)
    {
        float pos = window_len * (i + 1) / (num_lines + 1);
        if(horizontal) {
            grid[i*2].position = sf::Vector2f(20, pos);
            grid[i*2+1].position = sf::Vector2f(window_len - 20, pos);
        } else
        {
            grid[i*2].position = sf::Vector2f(pos, 20);
            grid[i*2+1].position = sf::Vector2f(pos, window_len - 20);
        }
        grid[i*2].color = grid[i*2+1].color = 
            sf::Color(grid_color[0], grid_color[1], grid_color[2]);
    }
    return {grid};
}
/*Показать график по двум входным массивам*/
bool Qt::Visualize(const vec& u, double (*func)(double x), Color linecolor) const
{
    if(u.empty()) return false;
    vec y_values(u.size());
    for(std::size_t i = 0; i < u.size(); ++i)
    {
        y_values[i] = func(u[i]);
    }
    vec x_scaled = ScalePerform(u);
    vec y_scaled = ScalePerform(y_values);
    /*Подготовка графика*/
    sf::VertexArray graph(sf::PrimitiveType::LineStrip, u.size());
    std::size_t window_height = qt_->getSize().y;
    for(std::size_t i = 0; i < u.size(); ++i)
    {
        double y_pos = window_height - y_scaled[i];
        graph[i].position = sf::Vector2f(x_scaled[i], y_pos);
        graph[i].color = sf::Color(linecolor[0], linecolor[1], linecolor[2]);
    }
    /*Создание сетки*/
    auto grid_x = CreateGrid(u, false);
    auto grid_y = CreateGrid(y_values, true);
    /*отрисовка*/
    while (qt_->isOpen())
    {
        sf::Event event;
        while (qt_->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                qt_->close();
                return true;
            }
        }
        qt_->clear(sf::Color::White);
        /*Сетка*/
        for(const auto& line : grid_x) qt_->draw(line);
        for(const auto& line : grid_y) qt_->draw(line);
        /*график*/
        qt_->draw(graph);
        qt_->display();
        /*Небольшая задержка для снижения нагрузки*/
        sf::sleep(sf::milliseconds(16));
    }
    return true;
}
