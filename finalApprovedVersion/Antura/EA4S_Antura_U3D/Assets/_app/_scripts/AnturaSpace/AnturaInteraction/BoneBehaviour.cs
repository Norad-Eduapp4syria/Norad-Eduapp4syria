﻿using UnityEngine;
using System.Collections;

namespace EA4S
{
    public class BoneBehaviour : MonoBehaviour
    {

        #region EXPOSED MEMBERS
        [SerializeField]
        private Rigidbody m_oBoneRigidbody;
        [SerializeField]
        private GameObject m_oParticle;
        [SerializeField]
        private float m_oParticleTime;
        [SerializeField]
        private Sfx m_oSfxOnPoof;

        [Header("Simple Throw")]

        [SerializeField]
        private Vector3 m_v3DirectionMinValues;
        [SerializeField]
        private Vector3 m_v3DirectionMaxValues;
        [SerializeField]
        private float m_fThrowMinMagnitude = 0f;
        [SerializeField]
        private float m_fThrowMaxMagnitude = 10f;
        [SerializeField]
        private ForceMode m_eThrowForceMode;

        [Header("Rotation")]

        [SerializeField]
        private float m_fRotationMinMagnitude = 0f;
        [SerializeField]
        private float m_fRotationMaxMagnitude = 10f;
        [SerializeField]
        private ForceMode m_eRotationForceMode;

        [Header("Drag")]

        [SerializeField]
        private float m_fDragThrowMagnitudeScaling = 1f;
        [SerializeField]
        private float m_fTimeSampling = 0.0333f;
        [SerializeField]
        private ForceMode m_eReleaseForceMode;
        #endregion

        #region PRIVATE MEMBERS
        private GameObject m_oParticleInstance;
        bool m_bIsDragged = false;
        private Vector3 m_v3LastPosition;
        private float m_fTimeProgression=0;
        #endregion

        private static GameObject s_oParticleRootContainer;

        #region GETTER/SETTER

        public float boneRotation_MaxMagnitude
        {
            get { return m_fRotationMaxMagnitude; }
            set { m_fRotationMaxMagnitude = value; }
        }

        public float boneRotation_MinMagnitude
        {
            get { return m_fRotationMinMagnitude; }
            set { m_fRotationMinMagnitude = value; }
        }

        public Rigidbody boneRigidbody
        { get;set; }

        public bool isDragging()
        {
            return m_bIsDragged;
        }

        #endregion

        #region INTERNALS
        void Start()
        {

            if (m_fRotationMaxMagnitude < m_fRotationMinMagnitude ||
                m_fThrowMaxMagnitude < m_fThrowMinMagnitude ||
                m_v3DirectionMinValues.x > m_v3DirectionMaxValues.x ||
                m_v3DirectionMinValues.y > m_v3DirectionMaxValues.y ||
                m_v3DirectionMinValues.z > m_v3DirectionMaxValues.z )
            {
                Debug.Log("Warning, unvalid min/max values");
            }

            //build root for cookies particles
            if(s_oParticleRootContainer==null)
            {
                GameObject _oTempBase = new GameObject();
                s_oParticleRootContainer = Instantiate(_oTempBase);
                s_oParticleRootContainer.name = "[CookieParticles]";
                Destroy(_oTempBase);

                s_oParticleRootContainer.transform.position = Vector3.zero;
            }

        }

        void Update()
        {

            if(m_bIsDragged) //if this bone is being dragged
            {
                m_fTimeProgression += Time.deltaTime;

                if(m_fTimeProgression>=m_fTimeSampling)
                {
                    m_v3LastPosition = transform.position;//Store dragging data to prepare for the releasing throw
                    m_fTimeProgression -= m_fTimeSampling;
                }
                

                //set the bone position on the pointer(x,y) at it's current distance from the camera
                float _fCameraDistance = Mathf.Abs(Camera.main.transform.position.z - transform.position.z);
                transform.position = Camera.main.ScreenToWorldPoint(new Vector3(Input.mousePosition.x, Input.mousePosition.y, _fCameraDistance));
                   
                //now keep it on an imaginary plane inclined to 45 degree by setting z equal to y
                transform.position=new Vector3(transform.position.x, transform.position.y, transform.position.y);

            }

        }

        //private void OnDisable()
        //{
        //    Poof(m_oParticleTime);
        //}

        void OnDestroy()
        {
            AudioManager.I.StopSfx(m_oSfxOnPoof);
            CancelInvoke();
        }
        #endregion

        #region PUBLIC FUNCTIONS

        /// <summary>
        /// The bone is throw with the setted forces
        /// </summary>
        public void SimpleThrow()
        {

            m_oBoneRigidbody.isKinematic = true; //resets actives forces
            m_oBoneRigidbody.isKinematic = false;

            //disable collision and enabled after 0.5 sec for avoid that Antura collision shot bone away
            m_oBoneRigidbody.GetComponentInChildren<Collider>().enabled = false;
            StartCoroutine(EA4S.MissingLetter.Utils.LaunchDelay(0.5f, 
                delegate
                {
                    m_oBoneRigidbody.GetComponentInChildren<Collider>().enabled = true;
                }));

            ApplyDefaultForces();

        }

        public void Drag()
        {
           
            m_oBoneRigidbody.isKinematic = true; //resets actives forces

            gameObject.GetComponentInChildren<Collider>().isTrigger = true; //this way Antura won't eat it since collision won't happen

            m_bIsDragged = true;

            m_fTimeProgression = 0;

            m_v3LastPosition = transform.position;
        }

        public void LetGo()
        {
            
            m_oBoneRigidbody.isKinematic = false;

            gameObject.GetComponentInChildren<Collider>().isTrigger = false;

            m_bIsDragged = false;

            m_fTimeProgression = 0;

            //apply stored forces
            ApplyDragForces();
        }

        /// <summary>
        /// Plays the particle effect for the given time.
        /// </summary>
        /// <param name="fDuration"></param>
        public void Poof()
        {      
            if (m_oParticleInstance==null)
            {
                m_oParticleInstance = Instantiate<GameObject>(m_oParticle);

                //put cookie in the root
                if (s_oParticleRootContainer != null)
                {
                    m_oParticleInstance.transform.SetParent(s_oParticleRootContainer.transform);
                }

                
            }

            m_oParticleInstance.transform.position = transform.position;//put particle on cookie

            m_oParticleInstance.SetActive(true);
            foreach (var particles in m_oParticleInstance.GetComponentsInChildren<ParticleSystem>(true))
            {
                particles.Play();
            }

            AudioManager.I.PlaySfx(m_oSfxOnPoof);

            CancelInvoke("StopPoof");//if we were quick maybe the particle hasn't stopped yet, so try to cancel the old one;
            Invoke("StopPoof", m_oParticleTime);
        }
        #endregion

        /// <summary>
        /// Stop the particle effect.
        /// </summary>
        private void StopPoof()
        {
            if(m_oParticleInstance)
            {
                foreach (var particles in m_oParticleInstance.GetComponentsInChildren<ParticleSystem>(true))
                {
                    particles.Stop();
                }

                m_oParticleInstance.SetActive(false);
            }
            
        }

        #region PRIVATE FUNCTIONS

        /// <summary>
        /// Apply the default forces on the Rigidbody
        /// </summary>
        private void ApplyDefaultForces()
        {
            Vector3 _v3ThrowDirection = new Vector3(
                Random.Range(m_v3DirectionMinValues.x, m_v3DirectionMaxValues.x),
                Random.Range(m_v3DirectionMinValues.y, m_v3DirectionMaxValues.y),
                Random.Range(m_v3DirectionMinValues.z, m_v3DirectionMaxValues.z)
                );

            //Add rotation with random magnitude
            m_oBoneRigidbody.AddTorque(Random.insideUnitSphere.normalized * Random.Range(m_fRotationMinMagnitude, m_fRotationMaxMagnitude), m_eRotationForceMode);
            //Add translation
            m_oBoneRigidbody.AddForce(_v3ThrowDirection.normalized * Random.Range(m_fThrowMinMagnitude, m_fThrowMaxMagnitude), m_eThrowForceMode);
        }

        /// <summary>
        /// Apply the drag forces on the Rigidbody
        /// </summary>
        private void ApplyDragForces()
        {
            //Add rotation with random magnitude
            m_oBoneRigidbody.AddTorque(Random.insideUnitSphere.normalized * Random.Range(m_fRotationMinMagnitude, m_fRotationMaxMagnitude), m_eRotationForceMode);
            //Add translation
            m_oBoneRigidbody.AddForce((transform.position-m_v3LastPosition) * m_fDragThrowMagnitudeScaling, m_eReleaseForceMode);
        }

        #endregion
    }
}
