#include "MipmapCollection.h"

MipmapCollection::MipmapCollection(std::unique_ptr<Image> image)
{
    generate_mipmap(std::move(image)); 
}
 
MipmapCollection::~MipmapCollection()
{
 
}
 
std::tuple<int, int> MipmapCollection::get_level_dimensions(int level) const
{
    if(level >= m_mipmap_levels.size()) {
        return std::make_tuple(0, 0);
    }

    return std::make_tuple(full_width() >> level, full_height() >> level);
}
 
void MipmapCollection::generate_mipmap(std::unique_ptr<Image>&& image)
{
    auto max_level = max_level_for_image(*image);

    m_mipmap_levels.reserve(max_level);

    m_mipmap_levels.emplace_back(std::move(image));

    for(int lvl = 1; lvl < max_level; ++lvl) {
        auto lvl_image = m_mipmap_levels.back()->shrink_to_next_mipmap();
        m_mipmap_levels.emplace_back(std::move(lvl_image));
    }
}
 
const Image& MipmapCollection::get_image_level(int level) const
{
    return *m_mipmap_levels[level]; 
}
 
int MipmapCollection::max_level_for_image(const Image& image)
{
    int width = image.width();
    int height = image.height(); 

    int level = 0;

    while(width > 1 && height > 1) {
        width >>= 1;
        height >>= 1;

        level += 1;
    }

    return level;
}
 
