--randomly spawn ants after sometime. 
spawn_probability = 0.1

--if an ant will pick up a fight with another ant
--fight_probability = 0.001

--the fight will also propagate throughout the colony.


--antIndex ( incremented for every ant spawn)
ant_count = 0

ants = {}

function spawnAnt()
    local base_x = 100*math.random()
    local base_y = 100*math.random()
    local ant_width = 1

    local rectIndex = ENGINE.Shape.GetRectangle({
        vertices = {
          { base_x, base_y, 0 },   -- bottom-left
          {  base_x+ant_width, base_y, 0 },   -- bottom-right
          {  base_x+ant_width, base_y+ant_width  , 0 },   -- top-right
          {  base_x, base_y+ant_width, 0 }    -- top-left
        },
        colors = {
          { 1, 0, 0, 1 },   -- red (bottom-left)
          { 0, 1, 0, 1 },   -- green (bottom-right)
          { 0, 0, 1, 1 },   -- blue (top-right)
          { 1, 1, 0, 1 }    -- yellow (top-left)
        }
      })

    print("Rectangle Index")
    print(rectIndex)

    ant_count = ant_count + 1 
    local ant_index = ant_count
    -- local colony_id = findColony(ant_index)

    ENGINE.Physics(rectIndex,{
      position = {},
      velocity = {},
      rotation = {},
      rotation_velocity = {}
  
  })


end





----ant is a creature with ability to move around the 2d plane 
--- ant is characterised by a position in 2d plane, a rotation in 2d plane and it's colony_id. 

function callbackFunction()
    if(math.random() < spawn_probability) then
        print("Callback triggered")
        spawnAnt()
    end
end



