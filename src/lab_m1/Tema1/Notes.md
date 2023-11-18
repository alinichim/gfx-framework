### Tasks

- [ ] Implement game objects classes
    - [x] GameObject
        - [x] PassiveGameObject
            - [x] GameSlot
                - [x] BoardSlot
                - [x] HUDSlot
            - [x] BoardBase
            - [x] GamePoint
            - [x] HUDHealthBar
        - [ ] ActiveGameObject
            - [ ] Defender
            - [ ] Attacker
            - [ ] Projectile

### Issues

- when the player is out of points, next time it collects, the points appear at the bottom;

#### Attacker detection logic

```python
for defender in defenders:
    for attacker in attackers:
        if defender.color != attacker.color:
            continue
        if defender.lane != attacker.lane:
            continue
        if defender.x > attacker.x:
            continue

        # start shooting

        projectiles.append(projectile())

```