/**
 * spaint: LabelPropagator_CUDA.h
 * Copyright (c) Torr Vision Group, University of Oxford, 2015. All rights reserved.
 */

#ifndef H_SPAINT_LABELPROPAGATOR_CUDA
#define H_SPAINT_LABELPROPAGATOR_CUDA

#include "../interface/LabelPropagator.h"

namespace spaint {

/**
 * \brief An instance of this class can be used to propagate labels across surfaces in the scene using CUDA.
 */
class LabelPropagator_CUDA : public LabelPropagator
{
  //#################### CONSTRUCTORS ####################
public:
  /**
   * \brief Constructs a CUDA-based label propagator.
   *
   * \param raycastResultSize                 The size of the raycast result (in pixels).
   * \param maxAngleBetweenNormals            The largest angle allowed between the normals of neighbouring voxels if extrapolation is to occur.
   * \param maxSquaredDistanceBetweenColours  The maximum squared distance allowed between the colours of neighbouring voxels if extrapolation is to occur.
   * \param maxSquaredDistanceBetweenVoxels   The maximum squared distance allowed between the positions of neighbouring voxels if extrapolation or interpolation are to occur.
   */
  LabelPropagator_CUDA(size_t raycastResultSize, float maxAngleBetweenNormals, float maxSquaredDistanceBetweenColours, float maxSquaredDistanceBetweenVoxels);

  //#################### PUBLIC MEMBER FUNCTIONS ####################
public:
  /** Override */
  virtual void interpolate_labels(const ITMFloat4Image *raycastResult, ITMLib::Objects::ITMScene<SpaintVoxel,ITMVoxelIndex> *scene) const;

  //#################### PRIVATE MEMBER FUNCTIONS ####################
private:
  /** Override */
  virtual void calculate_normals(const ITMFloat4Image *raycastResult, const ITMLib::Objects::ITMScene<SpaintVoxel,ITMVoxelIndex> *scene) const;

  /** Override */
  virtual void perform_extrapolation(SpaintVoxel::Label label, const ITMFloat4Image *raycastResult, ITMLib::Objects::ITMScene<SpaintVoxel,ITMVoxelIndex> *scene) const;
};

}

#endif
