# Physical Simulator

```plantuml
class Game

class Actor {
    +update(float stepTime)
    +render(RenderTarget* target)
    +addComponent(Component* component)
    +removeComponent(Component* component)
    -deque<Component*> mComponents
}

class Component {
    {abstract}+update(float stepTime)
    {abstract}+render(RenderTarget* target)
}

class Sprite {
    {abstract}+update(float stepTime)
    {abstract}+render(RenderTarget* target)
}

class Animation {
    {abstract}+update(float stepTime)
    {abstract}+render(RenderTarget* target)
}

class Background {
    {abstract}+update(float stepTime)
    {abstract}+render(RenderTarget* target)
}

Game "1" *-- "0..*" Actor

Actor "1" *-- "0..*" Component

Component <|-- Sprite

Sprite <|-- Animation
Sprite <|-- Background

```
