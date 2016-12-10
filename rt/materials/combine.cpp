#include <rt/materials/combine.h>

namespace rt
{
    void CombineMaterial::add(Material* material, float weight)
    {
        materials.push_back(std::make_pair(material, weight));
        Material::Sampling currentSampling = material->useSampling();
        if(getSamplingPriority(sampling) > getSamplingPriority(currentSampling))
        {
            sampling = currentSampling;
        }
    }
    RGBColor CombineMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const
    {
        //linear combination
        RGBColor color = RGBColor(0.0f, 0.0f, 0.0f);
		for(int i = 0; i < materials.size(); ++i)
		{
            //TODO: check if this is required if sampling = SAMPLING_ALL
			color = color + materials[i].second * materials[i].first->getReflectance(texPoint, normal, outDir, inDir);
		}
		return color;
    }
    RGBColor CombineMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const
    {
        //linear combination
        RGBColor color = RGBColor(0.0f, 0.0f, 0.0f);
		for(int i = 0; i < materials.size(); ++i)
		{
            //TODO: check if this is required if sampling = SAMPLING_ALL
			color = color + materials[i].second * materials[i].first->getEmission(texPoint, normal, outDir);
		}
		return color;
    }
    SampleReflectance CombineMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const
    {
        SampleReflectance sampleReflectance;
        //at most one of the combined materials requires sampling
        for (int i = 0; i < materials.size(); ++i) 
        {
            if (materials[i].first->useSampling() != Material::SAMPLING_NOT_NEEDED)
            {
                sampleReflectance = materials[i].first->getSampleReflectance(texPoint, normal, outDir);
                break;
            }    
        }
        return sampleReflectance;
    }
    Material::Sampling CombineMaterial::useSampling() const
    {   
        return sampling;
    }
    int getSamplingPriority(Material::Sampling samplingType)  
    {
        if(samplingType == Material::SAMPLING_NOT_NEEDED)
            return 0;
		else if(samplingType == Material::SAMPLING_SECONDARY)
            return 1;
		else if(samplingType == Material::SAMPLING_ALL)
            return 2;
    }
    Material::Sampling mapSamplingWithPriority(int priority)  
    {
        if(priority == 0)
            return Material::SAMPLING_NOT_NEEDED;
        else if(priority == 1)  
            return Material::SAMPLING_SECONDARY;
        else if(priority == 2)  
            return Material::SAMPLING_ALL;
    }
}