
var idleSet = false;
var idleAnimation = "look";

function Update()
{
	var playerController : ThirdPersonController = GetComponent(ThirdPersonController);
	var vel = playerController.GetSpeed();
	var PE : ParticleEmitter = GetComponentInChildren(ParticleEmitter);
	
	if (vel < 0.1)
	{
		PE.emit = false;
		if (!idleSet)
		{
			idleSet = true;
			var r = UnityEngine.Random.Range(1,6);
			if (r==1)
				idleAnimation = "look";
			if (r==2)
				idleAnimation = "kick";
			if (r==3)
				idleAnimation = "handstand";
			if (r==4)
				idleAnimation = "dance";
			if (r==5)
				idleAnimation = "jump";
		}
		animation.CrossFade(idleAnimation);
	}
	if (vel > 0.1 && vel < 2)
	{
		PE.emit = true;
		PE.maxEmission = 10;
		animation.CrossFade("walk");
		idleSet = false;
	}
	if (vel >= 2)
	{
		PE.emit = true;
		PE.maxEmission = 20;
		animation["run"].speed = 0.8f;
		animation.CrossFade("run");
		idleSet = false;
	}
}