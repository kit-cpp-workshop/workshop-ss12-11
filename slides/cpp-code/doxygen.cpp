/**
 * Returns the color value of the pixel at coordinate (p_x, p_y).
 *
 * @param p_x the X coordinate component, 
 *            with 0 <= p_x <= width - 1
 * @param p_y the Y coordinate component, 
 *            with 0 <= p_y <= height - 1
 * @return a reference to the color value at pixel (p_x, p_y)
 * @throws std::out_of_range if the passed coordinates exceed
 *                           the valid value range 
 */
Color24& getPixel(unsigned int p_x, unsigned int p_y);
