/**
 * itmx: FernRelocaliser.h
 * Copyright (c) Torr Vision Group, University of Oxford, 2017. All rights reserved.
 */

#ifndef H_ITMX_FERNRELOCALISER
#define H_ITMX_FERNRELOCALISER

#include "Relocaliser.h"

#include <FernRelocLib/Relocaliser.h>

namespace itmx {

/**
 * \brief An instance of this class allows performing camera relocalisation from RGB-D image pairs wrapping an instance
 *        of the Fern-Based InfiniTAM relocaliser.
 */
class FernRelocaliser : public Relocaliser
{
  //#################### ENUMS ####################
public:
  /**
   * Whether to always try to add a keyframe to the pose database or wait after a relocalisation is performed.
   * Can be used to avoid storing keyframes right after a tracking failure until we are sure that they are actually
   * good.
   */
  enum KeyframeAddPolicy { ALWAYS_TRY_ADD, DELAY_AFTER_RELOCALISATION };

  //#################### CONSTRUCTORS ####################
public:
  /**
   * \brief Constructs a FernRelocaliser.
   *
   * \param depthImageSize      The dimensions of the depth images that will be passed to the relocaliser.
   * \param viewFrustumMin      The minimum distance to consider in the depth images.
   * \param viewFrustumMax      The maximum distance to consider in the depth images.
   * \param harvestingThreshold The threshold used when deciding whether to store a keyframe.
   * \param numFerns            The number of ferns used for relocalisation.
   * \param decisionsPerFern    The number of decisions that are performed in each fern.
   * \param keyframeAddPolicy   The policy to adapt to decide whether to store keyframes right after tracking failures.
   */
  FernRelocaliser(Vector2i depthImageSize,
                  float viewFrustumMin,
                  float viewFrustumMax,
                  float harvestingThreshold,
                  int numFerns,
                  int decisionsPerFern,
                  KeyframeAddPolicy keyframeAddPolicy = DELAY_AFTER_RELOCALISATION);

  //#################### PUBLIC STATIC MEMBER FUNCTIONS ####################
public:
  /**
   * \brief Returns the default harvesting threshold.
   *
   * \return The default harvesting threshold.
   */
  static float get_default_harvesting_threshold();

  /**
   * \brief Returns the default policy used when adding keyframes to the relocaliser.
   *
   * \return The default policy used when adding keyframes to the relocaliser.
   */
  static FernRelocaliser::KeyframeAddPolicy get_default_keyframe_add_policy();

  /**
   * \brief Returns the default number of decisions per each fern.
   *
   * \return The default number of decisions per each fern.
   */
  static int get_default_num_decisions_per_fern();

  /**
   * \brief Returns the default number of ferns.
   *
   * \return The default number of ferns.
   */
  static int get_default_num_ferns();

  //#################### PUBLIC VIRTUAL MEMBER FUNCTIONS ####################
public:
  /** Override */
  virtual boost::optional<Result> relocalise(const ITMUChar4Image *colourImage,
                                             const ITMFloatImage *depthImage,
                                             const Vector4f &depthIntrinsics) const;

  /** Override */
  virtual void reset();

  /** Override */
  virtual void train(const ITMUChar4Image *colourImage, const ITMFloatImage *depthImage,
                     const Vector4f& depthIntrinsics, const ORUtils::SE3Pose& cameraPose);

  //#################### PRIVATE TYPEDEFS ####################
private:
  typedef FernRelocLib::Relocaliser<float> WrappedRelocaliser;
  typedef boost::shared_ptr<WrappedRelocaliser> WrappedRelocaliser_Ptr;

  //#################### PRIVATE MEMBER VARIABLES ####################
private:
  /** The number of decisions per fern. */
  int m_decisionsPerFern;

  /** The size of the input depth images. */
  Vector2i m_depthImageSize;

  /** The keyframe harvesting threshold. */
  float m_harvestingThreshold;

  /**
   * The policy deciding whether a frame for which the train function is called can be actually
   * integrated in the Fern conservatory.
   */
  KeyframeAddPolicy m_keyframeAddPolicy;

  /** The delay before trying to add another keyframe to the Fern conservatory. */
  mutable uint32_t m_keyframeDelay;

  /** The number of ferns to use for relocalisation. */
  int m_numFerns;

  /** The minimum and maximum range of the depth images. */
  Vector2f m_rangeParameters;

  /** The wrapped relocaliser. */
  WrappedRelocaliser_Ptr m_relocaliser;
};

}

#endif