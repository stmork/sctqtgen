pipeline
{
	agent any

	stages
	{
		stage('Build')
		{
			steps
			{
				sh """
				test -f Makefile && make clean distclean
				qmake -r
				make -j
				"""
			}
		}
	}

	post
	{
		always
		{
			chuckNorris()
			step([$class: 'Mailer', recipients: 'linux-dev@morknet.de'])
		}
	}
}
