# 2D Particle System

2D Particle System - небольшой движок 2D частиц, написанный при помощи SFML.

[Видео демонстрация работы](https://youtu.be/4Rh9qTNAC9o)

Тайм-коды по всей функциональности в описании

![Главное окно партиклов](https://github.com/AlexPrime2023/2DParticleSystem/assets/146464675/92a92cec-bd18-4f86-8c3a-846809cb3159)

### Функциональность

<ul>
    <li>Задание максимального числа партиклов;</li>
    <li>Задание позиции эмиттера;</li>
    <li>Задание радиуса эмиттера;</li>
    <li>Задание время жизни партикла;</li>
    <li>Задание скорости партикла;</li>
    <li>Задание размера партикла;</li>
    <li>Задание угловой скорости партикла;</li>
    </br>
    <li>Задание разной формы эмиттера (Sphere, Cone, Plane);</li>
    </br>
    <li>Рисование хвостов партиклов;</li>
    <li>Задание длины следа хвоста;</li>
    </br>
    <li>Задание постоянного цвета партикла;</li>
    </br>
    <li>Задание начального цвета партикла;</li>
    <li>Задание конечного цвета партикла;</li>
    <li>Задание Easing кривой для изменения цвета партикла во времени;</li>
    <li>Задание Easing кривой для изменения прозрачности партикла во времени;</li>
    </br>
    <li>Задание Easing кривой для изменения размера партикла во времени;</li>
    </br>
    <li>Задание вектора силы на партикл;</li>
    <li>Задание массы партикла;</li>
    <li>Задание Easing кривой для изменения силы воздействия на партикл во времени.</li>
</ul>

### Добавление новой функциональности

<ul>
    <li>Добавлять свой эмиттер (менять форму);</li>
    <li>Добавлять свои Easing кривые.</li>
</ul>

Для добавления своего эмиттера (изменение формы) необходимо поместить *.h и *.cpp файл в папку Emitters.

В этих файлах унаследоваться от Emitters и переопределить 3 метода:
<ul>
    <li>calculatePosition (вычисление позиции новых партиклов при их создании);</li>
    <li>calculateVelocity (вычисление вектора скорости "выталкивания" партиклов);</li>
    <li>calculateAngle (вычисление "вращения" партиклов).</li>
</ul>

```h
class SphereEmitter : public Emitter
{
public:
	sf::Vector2f calculatePosition() override;
	sf::Vector2f calculateVelocity() override;
	float calculateAngle() override;
};
```

```cpp
sf::Vector2f SphereEmitter::calculatePosition()
{
    return m_emitterPosition;
}

sf::Vector2f SphereEmitter::calculateVelocity()
{
    float theta = MathUtils::degToRad(std::rand() % 360);
    float phi = MathUtils::degToRad(std::rand() % 180);

    float x = m_emitterRadius * std::sin(phi) * std::cos(theta);
    float y = m_emitterRadius * std::sin(phi) * std::sin(theta);

    sf::Vector2f direction = sf::Vector2f(x, y);
    sf::Vector2f normalizedDirection = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);

    return normalizedDirection;
}

float SphereEmitter::calculateAngle()
{
    return 0.0f;
}
```

Для добавления своей easing кривой эмиттера (изменение формы) необходимо в файле <b>EasingCurves.h</b> создать свой класс кривой и переопределить метод *interpolate*.

```cpp
class LinearEasing : public EasingCurve {
public:
    float interpolate(float t) const override {
        return t;
    }
};
```

### Недоработки (TODO)
<ul>
    <li>
        Разнести все по пространствам имен (namespace);
    </li>
    <li>
    Немного не доработаны кривые/формы эмиттеров в 2D системе партиклов (они работают и все с ними прекрасно, но хотелось бы большей гибкости. Аналогично с формой эмиттеров);
    </li>
    <li>
    Возможна оптимизация по ресурсам.
    </li>
</ul>
