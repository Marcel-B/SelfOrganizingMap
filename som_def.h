struct parameter
{
  unsigned long map_x;
  unsigned long map_y;
  unsigned long depth;
};
class Som
{
public:
  Som() : map_x(0), map_y(0), map_z(0) {}
  Som(unsigned long x, unsigned long y, unsigned long z);
  ~Som();

private:
  double ***map;
  unsigned long map_x;
  unsigned long map_y;
  unsigned long map_z;
  Som* init();
}; // Som

struct map
{
  // y - x - z
  double ***weights;
};
void kill_memory(const parameter &para, map *som);
void init_networt(const parameter &parameter);
