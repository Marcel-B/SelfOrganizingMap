struct parameter
{
  unsigned long map_x;
  unsigned long map_y;
  unsigned long depth;
};
struct map
{
  // y - x - z
  double ***weights;
};
void init_networt(const parameter &parameter);
